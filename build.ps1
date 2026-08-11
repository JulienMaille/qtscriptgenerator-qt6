[CmdletBinding()]
param(
    [ValidateSet("Debug", "Release", "All")]
    [string] $Configuration = "All",

    [ValidateSet("CMake", "NMake")]
    [string] $Backend = "CMake",

    [string] $QtPrefix = $env:QT_ROOT_DIR,

    [string] $QtScriptPrefix = $env:QTSCRIPT_PREFIX,

    [ValidateSet("x64")]
    [string] $Architecture = "x64",

    [string] $Generator = "Ninja Multi-Config",

    [string] $BuildDirectory = ".cmake",

    [string] $VsDevCmd = ""
)

$ErrorActionPreference = "Stop"

$portRoot = $PSScriptRoot
. (Join-Path $portRoot "build-config.ps1")
$QtPrefix = Resolve-QtPrefix $QtPrefix
$QtScriptPrefix = Resolve-QtScriptPrefix $QtScriptPrefix $QtPrefix

function Initialize-MsvcEnvironment {
    param(
        [string] $VsDevCmdPath,
        [string] $TargetArchitecture
    )

    if (-not $VsDevCmdPath) {
        $vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
        if (-not (Test-Path -LiteralPath $vswhere)) {
            throw "Visual Studio Installer's vswhere.exe was not found: $vswhere"
        }
        $installationPath = & $vswhere -latest -products * `
            -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
            -property installationPath
        if (-not $installationPath) {
            throw "Visual Studio with the MSVC x64 toolchain was not found"
        }
        $VsDevCmdPath = Join-Path $installationPath "Common7\Tools\VsDevCmd.bat"
    }

    if (-not (Test-Path -LiteralPath $VsDevCmdPath)) {
        throw "Visual Studio environment script does not exist: $VsDevCmdPath"
    }

    $environment = cmd.exe /d /c `
        "call `"$VsDevCmdPath`" -arch=$TargetArchitecture -host_arch=$TargetArchitecture >nul 2>&1 && set"
    if ($LASTEXITCODE -ne 0) {
        throw "Visual Studio environment setup failed: $VsDevCmdPath"
    }
    foreach ($line in $environment) {
        if ($line -match '^([^=]+)=(.*)$') {
            [Environment]::SetEnvironmentVariable($Matches[1], $Matches[2], "Process")
        }
    }
}

if ($Backend -eq "NMake") {
    $legacyArguments = @{
        Configuration = $Configuration
        QtPrefix = $QtPrefix
        QtScriptPrefix = $QtScriptPrefix
        Architecture = $Architecture
    }
    if ($VsDevCmd) {
        $legacyArguments["VsDevCmd"] = $VsDevCmd
    }

    & (Join-Path $portRoot "build-nmake.ps1") @legacyArguments
    if ($LASTEXITCODE -ne 0) {
        exit $LASTEXITCODE
    }
    return
}

$cmakeCommand = Get-Command cmake -ErrorAction SilentlyContinue
if (-not $cmakeCommand) {
    throw "CMake was not found on PATH"
}

foreach ($requiredDirectory in @($QtPrefix, $QtScriptPrefix)) {
    if (-not (Test-Path -LiteralPath $requiredDirectory -PathType Container)) {
        throw "Required Qt 6 prefix does not exist: $requiredDirectory"
    }
}

if ($Generator -match "Ninja") {
    if (-not (Get-Command ninja -ErrorAction SilentlyContinue) -or
        -not (Get-Command cl.exe -ErrorAction SilentlyContinue)) {
        Initialize-MsvcEnvironment -VsDevCmdPath $VsDevCmd -TargetArchitecture $Architecture
    }
    if (-not (Get-Command ninja -ErrorAction SilentlyContinue)) {
        throw "Ninja was not found on PATH"
    }
    if (-not (Get-Command cl.exe -ErrorAction SilentlyContinue)) {
        throw "MSVC cl.exe was not found after Visual Studio environment setup"
    }
}

$buildRoot = if ([System.IO.Path]::IsPathRooted($BuildDirectory)) {
    [System.IO.Path]::GetFullPath($BuildDirectory)
} else {
    [System.IO.Path]::GetFullPath((Join-Path $portRoot $BuildDirectory))
}
$logRoot = Join-Path $portRoot "logs"
New-Item -ItemType Directory -Force -Path $logRoot | Out-Null

$configurations = switch ($Configuration) {
    "Debug" { @("Debug") }
    "Release" { @("Release") }
    default { @("Release", "Debug") }
}

$isMultiConfigGenerator = $Generator -match "Visual Studio|Xcode|Ninja Multi-Config"
if (-not $isMultiConfigGenerator -and $configurations.Count -gt 1) {
    throw "The CMake generator '$Generator' is single-config; choose Debug or Release instead of All"
}

$prefixPath = "$QtPrefix;$QtScriptPrefix"
$configureArguments = @(
    "-S", $portRoot,
    "-B", $buildRoot,
    "-G", $Generator,
    "-DCMAKE_PREFIX_PATH=$prefixPath",
    "-DQT_BINDINGS_OUTPUT_ROOT=$portRoot",
    "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
)
if ($Generator -match "Visual Studio") {
    $configureArguments += @("-A", $Architecture)
}
if (-not $isMultiConfigGenerator) {
    $configureArguments += "-DCMAKE_BUILD_TYPE=$($configurations[0])"
}

$configureLog = Join-Path $logRoot "configure-cmake.log"
& $cmakeCommand.Source @configureArguments 2>&1 | Tee-Object -FilePath $configureLog
if ($LASTEXITCODE -ne 0) {
    throw "CMake configure failed with exit code $LASTEXITCODE. See $configureLog"
}

foreach ($configurationName in $configurations) {
    $buildArguments = @("--build", $buildRoot)
    if ($isMultiConfigGenerator) {
        $buildArguments += @("--config", $configurationName)
    }
    $buildArguments += "--parallel"

    $buildLog = Join-Path $logRoot ("build-cmake-{0}.log" -f $configurationName.ToLowerInvariant())
    & $cmakeCommand.Source @buildArguments 2>&1 | Tee-Object -FilePath $buildLog
    if ($LASTEXITCODE -ne 0) {
        throw "CMake build failed for $configurationName with exit code $LASTEXITCODE. See $buildLog"
    }
}

Write-Host "Qt 6 CMake build succeeded."
Write-Host "Plugins: $portRoot\plugins\script"
