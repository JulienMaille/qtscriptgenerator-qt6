[CmdletBinding()]
param(
    [ValidateSet("Debug", "Release", "All")]
    [string] $Configuration = "All",

    [string] $QtPrefix = "C:\Qt\6-build\qt-6.9.2-dynamic-msvc-x64",

    [string] $QtScriptPrefix = "C:\Qt\qtscript-qt6-port-codex\install",

    [ValidateRange(1000, 600000)]
    [int] $EvaluatorTimeoutMilliseconds = 30000
)

$ErrorActionPreference = "Stop"
$env:PATH = "$QtScriptPrefix\bin;$QtPrefix\bin;$env:PATH"
$env:QT_QPA_PLATFORM = "offscreen"
$testRoot = $PSScriptRoot
$logRoot = Join-Path $testRoot "logs"
New-Item -ItemType Directory -Force -Path $logRoot | Out-Null

$sourceExtensions = @(".pro", ".pri", ".h", ".cpp")
$compatReferences = foreach ($sourceRoot in @(
    (Join-Path $PSScriptRoot "qtbindings"),
    (Join-Path $PSScriptRoot "generated_cpp"))) {
    Get-ChildItem -LiteralPath $sourceRoot -Recurse -File |
        Where-Object { $sourceExtensions -contains $_.Extension.ToLowerInvariant() } |
        Where-Object { $_.FullName -notmatch '\\(?:debug|release)\\' } |
        Select-String -Pattern "Core5Compat" -SimpleMatch
}
if ($compatReferences) {
    throw "Qt5Compat source dependency detected:`n$($compatReferences -join [Environment]::NewLine)"
}

$vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path -LiteralPath $vswhere)) {
    throw "vswhere.exe is required to locate dumpbin.exe: $vswhere"
}
$dumpbin = & $vswhere -latest -products * -find "VC\Tools\MSVC\**\bin\Hostx64\x64\dumpbin.exe" |
    Select-Object -First 1
if (-not $dumpbin) {
    throw "Could not locate the x64 MSVC dumpbin.exe"
}

$configurations = switch ($Configuration) {
    "Debug" { @("debug") }
    "Release" { @("release") }
    default { @("release", "debug") }
}

function Invoke-Evaluator {
    param(
        [Parameter(Mandatory = $true)] [string] $Evaluator,
        [Parameter(Mandatory = $true)] [string[]] $Arguments,
        [Parameter(Mandatory = $true)] [string] $Label,
        [int] $TimeoutMilliseconds = 30000
    )

    $safeLabel = $Label -replace '[^A-Za-z0-9_.-]', '_'
    $stdoutPath = Join-Path $logRoot "$safeLabel.stdout.log"
    $stderrPath = Join-Path $logRoot "$safeLabel.stderr.log"
    Remove-Item -LiteralPath $stdoutPath, $stderrPath -Force -ErrorAction SilentlyContinue

    # ProcessStartInfo receives one command-line string on Windows. Quote each
    # argument so test paths remain valid when the checkout is under a path
    # containing spaces.
    $quotedArguments = @($Arguments | ForEach-Object {
        '"' + $_.Replace('"', '\"') + '"'
    })
    $startInfo = New-Object System.Diagnostics.ProcessStartInfo
    $startInfo.FileName = $Evaluator
    $startInfo.Arguments = $quotedArguments -join ' '
    $startInfo.WorkingDirectory = $testRoot
    $startInfo.UseShellExecute = $false
    $startInfo.CreateNoWindow = $true
    $startInfo.RedirectStandardOutput = $true
    $startInfo.RedirectStandardError = $true

    $process = New-Object System.Diagnostics.Process
    $process.StartInfo = $startInfo
    [void]$process.Start()
    $stdoutTask = $process.StandardOutput.ReadToEndAsync()
    $stderrTask = $process.StandardError.ReadToEndAsync()

    if (-not $process.WaitForExit($TimeoutMilliseconds)) {
        & taskkill.exe /PID $process.Id /T /F | Out-Null
        [void]$process.WaitForExit(5000)
        $stdout = $stdoutTask.Result
        $stderr = $stderrTask.Result
        [System.IO.File]::WriteAllText($stdoutPath, $stdout)
        [System.IO.File]::WriteAllText($stderrPath, $stderr)
        $process.Dispose()
        throw "$Label timed out after $TimeoutMilliseconds ms; see $stderrPath`n$stdout$stderr"
    }
    # WaitForExit() without a timeout drains asynchronous output handlers.
    $process.WaitForExit()
    $stdout = $stdoutTask.Result
    $stderr = $stderrTask.Result
    [System.IO.File]::WriteAllText($stdoutPath, $stdout)
    [System.IO.File]::WriteAllText($stderrPath, $stderr)
    $exitCode = $process.ExitCode
    $process.Dispose()

    if ($exitCode -ne 0) {
        throw "$Label failed with exit code $($exitCode).`n$stdout$stderr"
    }
}

foreach ($name in $configurations) {
    $evaluator = Join-Path $PSScriptRoot "qtbindings\qs_eval\$name\qs_eval.exe"
    if (-not (Test-Path -LiteralPath $evaluator)) {
        throw "Evaluator is missing for $name. Run build.ps1 first: $evaluator"
    }

    $debugBuild = $name -eq "debug"
    $pluginBinaries = Get-ChildItem -LiteralPath (Join-Path $PSScriptRoot "plugins\script") -Filter "qtscript_*.dll" |
        Where-Object { ($_.BaseName -match 'd$') -eq $debugBuild }
    foreach ($binary in @($pluginBinaries) + @(Get-Item -LiteralPath $evaluator)) {
        $dependencies = & $dumpbin /nologo /dependents $binary.FullName
        if ($dependencies -match "Qt6Core5Compatd?\.dll") {
            throw "Qt5Compat binary dependency detected in $($binary.FullName)"
        }
    }
    Write-Host "No Qt5Compat binary dependencies: $name"

    Invoke-Evaluator -Evaluator $evaluator -Arguments @("--scripttools-smoke") `
        -Label "$name-scripttools-smoke" -TimeoutMilliseconds $EvaluatorTimeoutMilliseconds
    Write-Host "QtScriptTools debugger smoke test passed: $name"

    foreach ($testName in @(
        "core-smoke.js", "core-regressions-smoke.js",
        "gui-smoke.js", "gui-regressions-smoke.js",
        "network-smoke.js", "network-regressions-smoke.js",
        "sql-smoke.js", "sql-regressions-smoke.js",
        "widgets-smoke.js", "widgets-regressions-smoke.js",
        "printsupport-smoke.js", "printsupport-regressions-smoke.js",
        "uitools-smoke.js", "uitools-regressions-smoke.js",
        "qt6-additions-smoke.js"
    )) {
        $smokeTest = Join-Path $PSScriptRoot "tests\$testName"
        Invoke-Evaluator -Evaluator $evaluator -Arguments @($smokeTest) `
            -Label "$name-$($testName -replace '\.js$', '')" `
            -TimeoutMilliseconds $EvaluatorTimeoutMilliseconds
        Write-Host "$testName passed: $name"
    }
}
