#!/usr/bin/env bash
# Phase 0 proof-of-concept: VC++ 4.2 cl/link under Wine in Docker.
# 1) compile + link hello.c  2) run the result under Wine
# 3) confirm PE linker field == 4.20  4) confirm two links are byte-identical
#    (frozen clock = same TimeDateStamp in both images).

set -euo pipefail
IMAGE="${1:?usage: proof.sh <image>}"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
# Frozen clock for the linker's TimeDateStamp (fixed value, not "now").
# The wine loader is i386, so the preload lib must be too. LD_PRELOAD-based
# faketime with TZ=UTC pins every time() call to exactly this instant.
EPOCH='1997-08-11 23:13:32'

mkdir -p "$ROOT/build"

# Run as the host uid: the bind-mount is owned by uid $(id -u), and wine
# refuses to create its prefix in a directory not owned by the process user.
run() { docker run --rm --user "$(id -u):$(id -g)" -e HOME=/tmp \
        -v "$ROOT:/work" -w /work "$IMAGE" "$@"; }
# Same, with the frozen clock (LD_PRELOAD faketime, wine loader is i386).
runft() {
    docker run --rm --user "$(id -u):$(id -g)" -e HOME=/tmp \
        -e TZ=UTC \
        -e LD_PRELOAD="/usr/lib/x86_64-linux-gnu/faketime/libfaketime.so.1:/usr/lib/i386-linux-gnu/faketime/libfaketime.so.1" \
        -e FAKETIME="@$EPOCH" \
        -v "$ROOT:/work" -w /work "$IMAGE" "$@"
}

echo "== boot wine prefix =="
run bash -c 'true' >/dev/null

echo "== compile (cl /MT /GX) =="
run bash -c 'cd /work/build && wine "Z:\opt\msvc420\bin\CL.EXE" -c /MT /GX /Od Z:/work/docker/hello/hello.c'

echo "== link (twice, frozen clock) =="
for i in 1 2; do
    runft bash -c "cd /work/build && wine \"Z:\opt\msvc420\bin\LINK.EXE\" /MACHINE:IX86 /SUBSYSTEM:CONSOLE /OUT:hello$i.exe hello.obj libcmt.lib kernel32.lib"
done

echo "== run under Wine =="
run wine /work/build/hello1.exe

echo "== PE check =="
run python3 /work/tools/checkpe.py /work/build/hello1.exe

echo "== determinism =="
if cmp "$ROOT/build/hello1.exe" "$ROOT/build/hello2.exe"; then
    echo "DETERMINISM=PASS (byte-identical links)"
else
    echo "DETERMINISM=DIFFER"
fi