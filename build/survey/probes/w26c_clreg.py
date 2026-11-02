#!/usr/bin/env python3
"""Dump .text of a w26c CL obj (all __function sections). Usage: ... w26c_clreg.py <objname>"""
import subprocess, sys, os
sys.path.insert(0, "tools")
import fitobj
secs, defs = fitobj.read_obj(sys.argv[1])
idx = 0
for s in secs:
    nm = s["name"]
    if nm in (".drectve", ".debug$F", ".debug$S", ".comment", ".data", ".rdata"): continue
    if nm.startswith(".text"): continue
    open("/tmp/x.bin", "wb").write(bytes(s["content"]))
    r = subprocess.run(["objdump", "-D", "-b", "binary", "-m", "i386", "-M", "intel", "/tmp/x.bin"],
                       capture_output=True, text=True)
    body = r.stdout.split("<.data>:", 1)[-1].strip()
    print("== %s (%d B) ==" % (nm, len(s["content"])))
    print(body)
    idx += 1
if not idx:   # plain .text (no /Gy split)
    for s in secs:
        if s["name"] == ".text":
            open("/tmp/x.bin", "wb").write(bytes(s["content"]))
            r = subprocess.run(["objdump", "-D", "-b", "binary", "-m", "i386", "-M", "intel", "/tmp/x.bin"],
                               capture_output=True, text=True)
            print("== .text (%d B) ==" % len(s["content"]))
            print(r.stdout.split("<.data>:", 1)[-1].strip())