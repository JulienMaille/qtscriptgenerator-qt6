[CmdletBinding()]
param(
    [ValidateSet("Debug", "Release", "All")]
    [string] $Configuration = "All",

    [string] $QtPrefix = $env:QT_ROOT_DIR,

    [string] $QtScriptPrefix = $env:QTSCRIPT_PREFIX,

    [ValidateSet("x64")]
    [string] $Architecture = "x64",

    [string] $VsDevCmd = ""
)

$ErrorActionPreference = "Stop"

$portRoot = $PSScriptRoot
. (Join-Path $portRoot "build-config.ps1")
$QtPrefix = Resolve-QtPrefix $QtPrefix
$QtScriptPrefix = Resolve-QtScriptPrefix $QtScriptPrefix $QtPrefix
$projectRoot = Join-Path $portRoot "qtbindings"
$qmake = Join-Path $QtPrefix "bin\qmake.exe"
$scriptModule = Join-Path $QtScriptPrefix "mkspecs\modules\qt_lib_script.pri"
$scriptToolsModule = Join-Path $QtScriptPrefix "mkspecs\modules\qt_lib_scripttools.pri"
$logRoot = Join-Path $portRoot "logs"

if (-not $VsDevCmd) {
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
    $VsDevCmd = Join-Path $installationPath "Common7\Tools\VsDevCmd.bat"
}

foreach ($requiredPath in @($VsDevCmd, $qmake, $scriptModule, $scriptToolsModule)) {
    if (-not (Test-Path -LiteralPath $requiredPath)) {
        throw "Required Qt 6 build input does not exist: $requiredPath"
    }
}

New-Item -ItemType Directory -Force -Path $logRoot | Out-Null

$targets = switch ($Configuration) {
    "Debug" { @("debug") }
    "Release" { @("release") }
    default { @("release", "debug") }
}
$targetCommand = ($targets | ForEach-Object { "nmake $_" }) -join " && "

$command = @(
    "call `"$VsDevCmd`" -arch=$Architecture -host_arch=$Architecture",
    "set `"QMAKEPATH=$QtScriptPrefix`"",
    "set `"QTSCRIPT_PREFIX=$QtScriptPrefix`"",
    "set `"PATH=$QtScriptPrefix\bin;$QtPrefix\bin;!PATH!`"",
    "cd /d `"$projectRoot`"",
    "`"$qmake`" -r qtbindings.pro",
    $targetCommand
) -join " && "

$logPath = Join-Path $logRoot ("build-nmake-{0}.log" -f $Configuration.ToLowerInvariant())
Push-Location $portRoot
try {
    & cmd.exe /v:on /d /s /c $command 2>&1 | Tee-Object -FilePath $logPath
    if ($LASTEXITCODE -ne 0) {
        throw "QtBindings nmake build failed with exit code $LASTEXITCODE. See $logPath"
    }
}
finally {
    Pop-Location
}

Write-Host "Qt 6 qmake/nmake build succeeded."
Write-Host "Plugins: $portRoot\plugins\script"
