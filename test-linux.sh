#!/usr/bin/env bash

set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
qt_prefix="${QT_ROOT_DIR:-}"
qt_script_prefix="${QTSCRIPT_PREFIX:-}"
configuration=Release
timeout_seconds=120
log_root="$repo_root/logs"
run_scripttools_smoke="${RUN_SCRIPTTOOLS_SMOKE:-0}"

while (($#)); do
    case "$1" in
        --qt-prefix) qt_prefix="$2"; shift 2 ;;
        --qt-script-prefix) qt_script_prefix="$2"; shift 2 ;;
        --configuration) configuration="$2"; shift 2 ;;
        --timeout) timeout_seconds="$2"; shift 2 ;;
        -h|--help)
            echo "Usage: $0 [--qt-prefix PATH] [--qt-script-prefix PATH] [--configuration Debug|Release|All] [--timeout SECONDS]"
            exit 0
            ;;
        *) echo "Unknown argument: $1" >&2; exit 2 ;;
    esac
done

[[ "$configuration" == Debug || "$configuration" == Release || "$configuration" == All ]] ||
    { echo "Configuration must be Debug, Release, or All." >&2; exit 2; }
[[ "$timeout_seconds" =~ ^[0-9]+$ && "$timeout_seconds" -ge 1 ]] ||
    { echo "Timeout must be a positive integer." >&2; exit 2; }
[[ "$run_scripttools_smoke" == 0 || "$run_scripttools_smoke" == 1 ]] ||
    { echo "RUN_SCRIPTTOOLS_SMOKE must be 0 or 1." >&2; exit 2; }
for command in ldd timeout; do
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

if grep -RIn --include='*.cpp' --include='*.h' --include='*.pri' --include='*.pro' \
    'Core5Compat' "$repo_root/qtbindings" "$repo_root/generated_cpp"; then
    echo "Qt5Compat source dependency detected." >&2
    exit 1
fi

export PATH="$qt_script_prefix/bin:$qt_prefix/bin:$PATH"
export LD_LIBRARY_PATH="$qt_script_prefix/lib:$qt_prefix/lib:${LD_LIBRARY_PATH:-}"
export QT_QPA_PLATFORM=offscreen
mkdir -p "$log_root"

if [[ "$configuration" == Debug ]]; then
    configurations=(debug)
elif [[ "$configuration" == Release ]]; then
    configurations=(release)
else
    configurations=(release debug)
fi

run_evaluator() {
    local evaluator="$1"
    local label="$2"
    shift 2
    local stdout_log="$log_root/$label.stdout.log"
    local stderr_log="$log_root/$label.stderr.log"
    local -a runner=("$evaluator")
    local -a environment=()

    if command -v xvfb-run >/dev/null; then
        runner=(xvfb-run -a -s "-screen 0 1280x1024x24" "${runner[@]}")
        environment=(env -u QT_QPA_PLATFORM)
    fi

    if ! "${environment[@]}" timeout --foreground "${timeout_seconds}s" "${runner[@]}" "$@" \
        >"$stdout_log" 2>"$stderr_log"; then
        echo "$label failed; see $stderr_log" >&2
        cat "$stdout_log" "$stderr_log" >&2
        exit 1
    fi
}

tests=(
    core-smoke.js core-regressions-smoke.js
    gui-smoke.js gui-regressions-smoke.js
    network-smoke.js network-regressions-smoke.js
    sql-smoke.js sql-regressions-smoke.js
    xml-smoke.js xml-regressions-smoke.js
    widgets-smoke.js widgets-regressions-smoke.js
    printsupport-smoke.js printsupport-regressions-smoke.js
    uitools-smoke.js uitools-regressions-smoke.js
    svg-smoke.js svg-regressions-smoke.js
    qt6-additions-smoke.js
)

for name in "${configurations[@]}"; do
    evaluator="$repo_root/qtbindings/qs_eval/$name/qs_eval"
    [[ -x "$evaluator" ]] ||
        { echo "Evaluator is missing for $name. Run build-linux.sh first: $evaluator" >&2; exit 1; }

    mapfile -t plugins < <(find "$repo_root/plugins/script" -maxdepth 1 -type f -name 'qtscript_*.so')
    ((${#plugins[@]})) || { echo "No plugins found for $name." >&2; exit 1; }
    for plugin in "${plugins[@]}" "$evaluator"; do
        if ldd "$plugin" 2>&1 | grep -Eq 'Core5Compat|Qt5Compat'; then
            echo "Qt5Compat binary dependency detected in $plugin" >&2
            exit 1
        fi
    done
    echo "No Qt5Compat binary dependencies: $name"

    if [[ "$run_scripttools_smoke" == 1 ]]; then
        run_evaluator "$evaluator" "$name-scripttools-smoke" --scripttools-smoke
        echo "QtScriptTools debugger smoke test passed: $name"
    else
        echo "QtScriptTools debugger smoke test skipped: $name"
    fi

    for test_name in "${tests[@]}"; do
        run_evaluator "$evaluator" "$name-${test_name%.js}" "$repo_root/tests/$test_name"
        echo "$test_name passed: $name"
    done
done
