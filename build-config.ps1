function Resolve-QtPrefix {
    param([string] $RequestedPrefix)

    if (-not $RequestedPrefix) {
        throw 'Specify -QtPrefix or set QT_ROOT_DIR.'
    }
    return [System.IO.Path]::GetFullPath($RequestedPrefix)
}

function Resolve-QtScriptPrefix {
    param(
        [string] $RequestedPrefix,
        [string] $QtPrefix
    )

    if ($RequestedPrefix) {
        return [System.IO.Path]::GetFullPath($RequestedPrefix)
    }

    $scriptPackage = Join-Path $QtPrefix 'lib\cmake\Qt6Script'
    $scriptModule = Join-Path $QtPrefix 'mkspecs\modules\qt_lib_script.pri'
    if ((Test-Path -LiteralPath $scriptPackage) -or (Test-Path -LiteralPath $scriptModule)) {
        return $QtPrefix
    }

    throw 'Specify -QtScriptPrefix or set QTSCRIPT_PREFIX when QtScript is not installed in the Qt prefix.'
}
