#!/usr/bin/env python3
"""Side-by-side diff of a CL probe obj .text vs the FA chunk bytes.

Usage: python3 build/survey/probes/w26c_cmp.py <cl.obj> <rva|name> [lendiff]
"""
import json
import os
import struct
import sys

REPO = "/home/terrence/Projects/fa-decomp"
os.chdir(REPO)
sys.path.insert(0, "tools")
sys.path.insert(0, "build/survey/probes")
import fitobj  # read_obj


def main():
    cl_obj, rva = sys.argv[1], int(sys.argv[2], 0)
    L = json.load(open("build/layout.json"))
    exe = open("FA/FA.EXE", "rb").read()
    cs = [c for c in L["text_chunks"] if c["rva"] == rva]
    fa = exe[cs[0]["off"]:cs[0]["off"] + cs[0]["size"]]
    secs, defs = fitobj.read_obj(cl_obj)
    text = next(s for s in secs if s["name"] == ".text")
    cl = bytes(text["content"])
    rels = sorted(set(r[0] for r in text["relocs"]))
    n = max(len(cl), len(fa))
    for o in range(0, n, 8):
        lines = []
        for src, dat in (("FA", fa), ("CL", cl)):
            b = dat[o:o + 8]
            if b:
                lines.append("%-3s %04x %-24s" % (src, o, b.hex(" ")))
        mark = ""
        fa_b = fa[o:o + 8]
        cl_b = cl[o:o + 8]
        if fa_b and cl_b and fa_b != cl_b and not (o <= (rels[0] if rels else -1)):
            mark = "*"
        for oo in rels:
            if o <= oo < o + 8:
                mark += "r%d " % (oo - o)
        print(("%s  " % mark) + "  ".join(lines))


if __name__ == "__main__":
    main()