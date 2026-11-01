#!/usr/bin/env python3
"""LibRead flag sweep (Workstream C wave 1): compile the REAL src/LibRead.c
under single-flag deltas and score each by the two artifact signatures:

  ART-A (early hintHndl load): 6-byte `8b 0d` located between `2b d1` and
         `8d 2c 92` (CL's early slot) vs only at FA's late slot; count = # of
         hintHndl loads in .text.
  ART-B (fused f3): `8b 6c 05 1f` present (fused) vs FA's lea+load pair
        `8d 4c 05 00 ... 8b 69 1f`.

Usage: python3 build/probe/pads/lrflags.py
"""
import os
import subprocess
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(os.path.dirname(HERE)))

FLAGSETS = [
    ("base",        "/c /O2 /Gy /G5"),
    ("O1",          "/c /O1 /Gy /G5"),
    ("O2-Gy-",      "/c /O2 /G5"),
    ("O2-G5-",      "/c /O2 /Gy"),
    ("Os",          "/c /O2 /Os /Gy /G5"),
    ("Ot-explicit", "/c /O2 /Ot /Gy /G5"),
    ("Ow",          "/c /O2 /Ow /Gy /G5"),
    ("Gs",          "/c /O2 /Gs /Gy /G5"),
    ("Gd",          "/c /O2 /Gd /Gy /G5"),
    ("Ox",          "/c /Ox /Gy /G5"),
    ("Ob2",         "/c /O2 /Ob2 /Gy /G5"),
    ("Gf",          "/c /O2 /Gf /Gy /G5"),
    ("O2-noi",      "/c /O2 /Oi- /Gy /G5"),
    ("Oa",          "/c /O2 /Oa /Gy /G5"),
    ("G3",          "/c /O2 /G3 /Gy"),
    ("G4",          "/c /O2 /G4 /Gy"),
    ("QIfdiv",      "/c /O2 /QIfdiv /Gy /G5"),
    ("QI05",        "/c /O2 /QI05 /Gy /G5"),
    ("Og-only",     "/c /Og /Gy /G5"),
    ("O2-Og-",     "/c /O2 /Og- /Gy /G5"),
]


def read_text(obj):
    d = open(obj, "rb").read()
    mach, nsec, ts, symptr, nsym, opthsz, ch = struct.unpack_from("<HHIIIHH", d, 0)
    o = 20 + opthsz
    for i in range(nsec):
        nm = d[o:o + 8].split(b"\0")[0].decode()
        vsz, va, rsz, rptr = struct.unpack_from("<IIII", d, o + 8)
        o += 40
        if nm == ".text":
            return d[rptr:rptr + rsz]


def signature(t):
    early = b"8b 0d" and (b"\x2b\xd1\x8b\x0d" in t)   # 2b d1 immediately followed
    lateonly = (b"\x2b\xd1\x8b\x0d" not in t)
    fused = b"\x8b\x6c\x05\x1f" in t
    lea = b"\x8d\x4c\x05\x00" in t
    hl = t.count(b"\x8b\x0d")
    return ("early-hh=%s late=%s fused-f3=%s lea-form=%s hhloads=%d"
            % (early, lateonly, fused, lea, hl))


for name, flags in FLAGSETS:
    obj = "build/pilot/LRF_%s.obj" % name
    cmd = ("wine Z:/opt/msvc420/bin/CL.EXE /nologo " + flags
           + " Z:/work/src/LibRead.c /FoZ:/work/" + obj)
    r = subprocess.run(["docker", "run", "--rm", "--user",
                        "%d:%d" % (os.getuid(), os.getgid()),
                        "-e", "HOME=/tmp", "-e", "FAKETIME_DISABLE_SHM=1",
                        "-v", REPO + ":/work", "-w", "/work", "fa-decomp-env",
                        "bash", "-c", cmd], capture_output=True, text=True)
    if not os.path.exists(REPO + "/" + obj):
        print("%-13s COMPILE-FAIL" % name)
        continue
    t = read_text(REPO + "/" + obj)
    print("%-13s len=%-3d %s" % (name, len(t), signature(t)))