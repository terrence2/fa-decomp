#!/usr/bin/env python3
"""Dump FA chunk bytes + a w26c CL obj (.text section) side by side.
Usage: python3 build/survey/probes/w26c_fachunk.py <hex_rva> [objname]
"""
import json, subprocess, sys, os
sys.path.insert(0, "tools")
import fitobj

exe = open("FA/FA.EXE", "rb").read()
L = json.load(open("build/layout.json"))
rva = int(sys.argv[1], 0)
c = [x for x in L["text_chunks"] if x["rva"] == rva][0]
fa = exe[c["off"]:c["off"] + c["size"]]
open("/tmp/fa.bin", "wb").write(fa)
obj = sys.argv[2] if len(sys.argv) > 2 else "w26c_x%06x" % rva
cl = b""
if os.path.exists("build/survey/probes/%s.obj" % obj):
    secs, defs = fitobj.read_obj("build/survey/probes/%s.obj" % obj)
    for s in secs:
        if s["name"] == ".text":
            cl = bytes(s["content"])
open("/tmp/cl.bin", "wb").write(cl)
print("FA %d B, CL %d B" % (len(fa), len(cl)))
for tag, f in (("FA", "/tmp/fa.bin"), ("CL", "/tmp/cl.bin")):
    r = subprocess.run(["objdump", "-D", "-b", "binary", "-m", "i386", "-M", "intel", f],
                       capture_output=True, text=True)
    body = r.stdout.split("<.data>:", 1)[-1].strip()
    print("=== %s ===\n%s" % (tag, body))