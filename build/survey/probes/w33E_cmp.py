#!/usr/bin/env python3
"""Side-by-side: probe obj .text vs FA chunk, with xed-style manual decode."""
import json, struct, sys
sys.path.insert(0, "tools")
import coff
from fitobj import read_obj

def coff_text(path):
    secs, defs = read_obj(path)
    t = next(s for s in secs if s["name"] == ".text")
    return t, secs, defs

def fa_chunk(rva, size=None):
    L = json.load(open("build/layout.json"))
    exe = open("FA/FA.EXE", "rb").read()
    cs = [c for c in L["text_chunks"] if c["rva"] == rva]
    c = cs[0]
    return exe[c["off"]:c["off"] + c["size"]], c

def run(objpath, rva):
    t, secs, defs = coff_text(objpath)
    fab, c = fa_chunk(rva)
    fa = fab
    relocs = t["relocs"]
    mask = set()
    for o, n_, ty in relocs:
        mask.update(range(o, o + 4))
    n = min(len(t["content"]), len(fa)) if len(fa) else len(fa)
    print("== %s vs %s  CL=%#x FA=%#x" % (objpath.rsplit("/",1)[0], c["name"], len(t["content"]), len(fa)))
    print("== defs:", ", ".join("%s@%#x(sec%d)" % (k, v[0], v[1]) for k, v in defs.items()))
    print("== relocs:", [(hex(o), n_, ty) for o, n_, ty in relocs])
    width = 16
    for i in range(0, max(len(t["content"]), len(fa)), width):
        row = []
        for j in range(i, min(i + width, max(len(t['content']), len(fa)))):
            cc = "%02x" % t["content"][j] if j < len(t["content"]) else "--"
            ff = "%02x" % fa[j] if j < len(fa) else "--"
            if j < min(len(t["content"]), len(fa)) and t["content"][j] != fa[j] and j not in mask:
                ff = "[%02x]" % fa[j]
            elif j in mask:
                cc = "(%02x)" % t["content"][j]
                ff = "(%02x)" % fa[j]
            row.append(cc + "/" + ff)
        print("%04x  %s" % (i, "  ".join(row)))

for objpath, rva in [pair.split(":") for pair in sys.argv[1:]]:
    run(objpath, int(rva, 0))