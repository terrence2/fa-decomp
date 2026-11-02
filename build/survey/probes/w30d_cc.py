#!/usr/bin/env python3
"""Quick single-probe compile (wave 30d). Usage: w30d_cc.py <src.c> <objname> [flags]
Compiles via docker CL 4.2, dumps .text hex + relocs of the obj."""
import os, subprocess, sys, json
REPO = "/home/terrence/Projects/fa-decomp"
os.chdir(REPO)
sys.path.insert(0, os.path.join(REPO, "tools"))
from swap import DOCKER_PLAIN  # noqa
sys.path.insert(0, os.path.join(REPO, "build/survey"))
import fitobj  # noqa

src, obj = sys.argv[1], sys.argv[2]
flags = sys.argv[3] if len(sys.argv) > 3 else "/c /O2 /Gy /G5"
outdir = "build/survey/probes"
cl = ("wine Z:/opt/msvc420/bin/CL.EXE /nologo " + flags +
      " Z:/work/%s /FoZ:/work/%s/%s.obj" % (src, outdir, obj))
r = subprocess.run(DOCKER_PLAIN % dict(uid=os.getuid(), gid=os.getgid(), cmd=cl),
                   shell=True, capture_output=True, text=True)
print(r.stdout.strip() or r.stderr.strip())
path = "%s/%s.obj" % (outdir, obj)
if os.path.exists(path):
    secs, defs = fitobj.read_obj(path)
    text = next(s for s in secs if s["name"] == ".text")
    print("text len %d:" % len(text["content"]))
    b = bytes(text["content"])
    for i in range(0, len(b), 16):
        print("%02x  %s" % (i, b[i:i+16].hex()))
    print("relocs:", text["relocs"])