#!/usr/bin/env python3
"""LibRead source/flag hunt (Workstream C), round 2 — variants built on the
REAL src/LibRead.c body (round 1 proved the f3 variable + f2 order are
load-bearing for the cmp/jl/lea forms).

Success = fitobj passes with NO --patch:
  'chunk _LibRead @ 0x78b50: cl code 0x9e + pad 0x2 = 0xa0'.

Usage: python3 build/probe/pads/lrsweep.py [name ...]"""
import json
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(os.path.dirname(HERE)))
MAPS = ["_hintHndl=?hintHndl@@3PAUT_HANDLE@@A",
        "_libTable=?libAccess@@3PAULIBACCESS@@A+4"]

real = open(REPO + "/src/LibRead.c").read()
body = real[real.index("extern void* hintHndl"):]

# ---- variant patches: list of (old, new) applied to the body ----
V = {}


def variant(name, subs, decl=""):
    for old, _ in subs:
        assert old in body, "variant %s: %r missing" % (name, old)
    V[name] = (subs, decl)


# --- hintHndl second-load placement (CL loads it @0x39, FA @0x4c) ---
variant("base", [])
variant("volhh", [("extern void* hintHndl;", "extern void* volatile hintHndl;")])
variant("hhvar", [("f3  = *(long*)(p35 + rc + 0x1f);",
                   "h2 = hintHndl;\n    f3  = *(long*)(p35 + rc + 0x1f);"),
                  ("MMUnlock(hintHndl)", "MMUnlock(h2)")], "    void* h2;\n")
variant("hhafter", [("hi  = f2 + f3;",
                     "hi  = f2 + f3;\n    h2 = hintHndl;"),
                    ("MMUnlock(hintHndl)", "MMUnlock(h2)")], "    void* h2;\n")
variant("hhpost", [("MMUnlock(hintHndl)", "MMUnlock((void*)*(void**)(void*)&hintHndl)")])

# --- f3 address materialization (CL fuses sib; FA lea ecx,[ebp+eax]) ---
variant("p3ptr", [("f3  = *(long*)(p35 + rc + 0x1f);",
                   "f3  = *(long*)((char*)p35 + rc + 0x1f);")])
variant("p3ptr2", [("f3  = *(long*)(p35 + rc + 0x1f);",
                    "f3  = *(long*)((char*)(p35 + rc) + 0x1f);")])
variant("p3u8", [("f3  = *(long*)(p35 + rc + 0x1f);",
                  "f3  = *(long*)((unsigned char*)(p35 + rc) + 0x1f);")])
variant("p3var", [("f3  = *(long*)(p35 + rc + 0x1f);",
                   "{ unsigned char* b = (unsigned char*)(p35 + rc);\n"
                   "      f3  = *(long*)(b + 0x1f); }")])
variant("p3f2ptr", [("f2  = *(long*)(p35 + rc + 0x1b);",
                     "f2  = *(long*)((char*)p35 + rc + 0x1b);")])
variant("p3all", [
    ("f1  = *(long*)(p35 + rc + 0x17);", "f1  = *(long*)((char*)p35 + rc + 0x17);"),
    ("f2  = *(long*)(p35 + rc + 0x1b);", "f2  = *(long*)((char*)p35 + rc + 0x1b);"),
    ("f3  = *(long*)(p35 + rc + 0x1f);", "f3  = *(long*)((char*)p35 + rc + 0x1f);")])


def make_src(name):
    subs, extra = V[name]
    src = body
    for old, new in subs:
        src = src.replace(old, new)
    if extra:
        src = src.replace("    unsigned long p35;", "    unsigned long p35;\n" + extra, 1)
    return src


def run(args):
    return subprocess.run(args, capture_output=True, text=True)


def sweep(names):
    es = json.loads("\n".join(l for l in open(REPO + "/tools/swap.json")
                              .read().splitlines() if not l.lstrip().startswith("//")))
    lib = [e for e in es if e["obj"] == "LibRead"][0]
    results = {}
    for nm in names:
        src = "%s/build/pilot/LR2_%s.c" % (REPO, nm)
        open(src, "w").write(make_src(nm))
        obj = "build/pilot/LR2_%s.obj" % nm
        cmd = ("wine Z:/opt/msvc420/bin/CL.EXE /nologo "
               + lib.get("flags", "/c /O2 /Gy /G5")
               + " Z:/work/build/pilot/LR2_%s.c /FoZ:/work/%s" % (nm, obj))
        r = run(["docker", "run", "--rm", "--user", "%d:%d" % (os.getuid(), os.getgid()),
                 "-e", "HOME=/tmp", "-e", "FAKETIME_DISABLE_SHM=1",
                 "-v", REPO + ":/work", "-w", "/work", "fa-decomp-env",
                 "bash", "-c", cmd])
        if not os.path.exists(REPO + "/" + obj):
            errs = [l for l in (r.stdout + r.stderr).splitlines()
                    if "ELFCLASS" not in l and l.strip()]
            results[nm] = ("COMPILE-FAIL", " ".join(errs)[:180])
            continue
        args = [sys.executable, REPO + "/tools/fitobj.py", obj, "0x78b50"]
        for m in MAPS:
            args += ["--map", m]
        f = run(args)
        resline = " | ".join(l for l in f.stdout.strip().splitlines()
                             if l.startswith("chunk ") or l.startswith("FATAL"))
        results[nm] = ("PASS" if f.returncode == 0 else "fail", resline or f.stderr[-200:])
    for nm, (st, msg) in results.items():
        print("%-9s %-13s %s" % (nm, st, msg))
    return results


if __name__ == "__main__":
    names = sys.argv[1:] or list(V)
    sweep(names)