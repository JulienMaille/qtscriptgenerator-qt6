#!/usr/bin/env bash

set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
qt_prefix="${QT_ROOT_DIR:-}"
qt_script_prefix="${QTSCRIPT_PREFIX:-}"
configuration=Release
build_directory="$repo_root/.cmake-linux"
parallel="$(nproc)"

while (($#)); do
    case "$1" in
        --qt-prefix) qt_prefix="$2"; shift 2 ;;
        --qt-script-prefix) qt_script_prefix="$2"; shift 2 ;;
        --configuration) configuration="$2"; shift 2 ;;
        --build-directory) build_directory="$2"; shift 2 ;;
        --parallel) parallel="$2"; shift 2 ;;
        -h|--help)
            echo "Usage: $0 [--qt-prefix PATH] [--qt-script-prefix PATH] [--configuration Debug|Release] [--build-directory PATH] [--parallel N]"
            exit 0
            ;;
        *) echo "Unknown argument: $1" >&2; exit 2 ;;
    esac
done

[[ "$configuration" == Debug || "$configuration" == Release ]] ||
    { echo "Configuration must be Debug or Release." >&2; exit 2; }
[[ "$parallel" =~ ^[0-9]+$ && "$parallel" -ge 1 ]] ||
    { echo "Parallel must be a positive integer." >&2; exit 2; }
for command in cmake ninja; do
    command -v "$command" >/dev/null ||
        { echo "$command was not found on PATH." >&2; exit 1; }
done
[[ -n "$qt_prefix" && -d "$qt_prefix" ]] ||
    { echo "Specify --qt-prefix or set QT_ROOT_DIR." >&2; exit 1; }

qt_prefix="$(cd "$qt_prefix" && pwd)"
if [[ -z "$qt_script_prefix" ]]; then
    if [[ -d "$qt_prefix/lib/cmake/Qt6Script" ||
          -f "$qt_prefix/mkspecs/modules/qt_lib_script.pri" ]]; then
        qt_script_prefix="$qt_prefix"
    else
        echo "Specify --qt-script-prefix or set QTSCRIPT_PREFIX when QtScript is not installed in the Qt prefix." >&2
        exit 1
    fi
fi
[[ -d "$qt_script_prefix" ]] ||
    { echo "QtScript prefix does not exist: $qt_script_prefix" >&2; exit 1; }
qt_script_prefix="$(cd "$qt_script_prefix" && pwd)"

if [[ "$build_directory" != /* ]]; then
    build_directory="$repo_root/$build_directory"
fi
mkdir -p "$build_directory"
build_directory="$(cd "$build_directory" && pwd)"

cmake -S "$repo_root" -B "$build_directory" -G Ninja \
    "-DCMAKE_BUILD_TYPE=$configuration" \
    "-DCMAKE_PREFIX_PATH=$qt_prefix;$qt_script_prefix" \
    "-DQT_BINDINGS_OUTPUT_ROOT=$repo_root" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$build_directory" --parallel "$parallel"

echo "Qt 6 bindings build succeeded ($configuration)."
echo "Plugins: $repo_root/plugins/script"
