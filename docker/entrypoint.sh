#!/usr/bin/env bash
# Container entrypoint: initialize the Wine prefix (headless) on first use,
# then run whatever command was passed. Every MSVC invocation goes through
# `wine` with a frozen clock by default (FA_EPOCH) so the linker timestamps
# are deterministic.
set -euo pipefail

export WINEPREFIX="${WINEPREFIX:-/work/.wine}"
export WINEDEBUG="${WINEDEBUG:--all}"
export FA_EPOCH="${FA_EPOCH:-1997-08-11 23:13:32 UTC}"

export MSVC_BIN='Z:\opt\msvc420\bin'
export INCLUDE='Z:\opt\msvc420\include'
export LIB='Z:\opt\msvc420\lib'
export TMP='Z:\tmp'

# Wrap the given command: raw shell command -> run as-is; anything else (cl,
# link, ...) -> wine + faketime prefix.
run_wine_cmd() {
    if [ "$#" -eq 0 ]; then
        "${SHELL:-/bin/bash}"
        return
    fi
    local prog="$1"; shift
    if command -v "$prog" >/dev/null 2>&1 && ! [ -e "/opt/msvc420/bin/$prog.EXE" ]; then
        exec "$prog" "$@"
    fi
    # Frozen clock: the 4.20 linker stamps link time into the PE. Freeze it to
    # the retail FA.EXE timestamp unless the caller opts out (FA_EPOCH=).
    if [ -n "${FA_EPOCH:-}" ]; then
        exec faketime "$FA_EPOCH" wine "$prog.EXE" "$@"
    fi
    exec wine "$prog.EXE" "$@"
}

if [ ! -e "$WINEPREFIX/.fa-ready" ]; then
    xvfb-run -a wineboot --init >/dev/null 2>&1 || wineboot --init >/dev/null 2>&1 || true
    wine cmd /c ver >/dev/null 2>&1 || true
    touch "$WINEPREFIX/.fa-ready" 2>/dev/null || true
fi

run_wine_cmd "$@"