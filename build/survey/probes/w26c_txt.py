#!/usr/bin/env python3
"""objdump the .text of a CL probe obj (with FA chunk juxtaposed).

Usage: python3 build/survey/probes/w26c_txt.py <cl.obj> <rva>
"""
import json
import os
import subprocess
import sys

REPO = "/home/terrence/Projects/fa-decomp"
os.chdir(REPO)
sys.path.insert(0, "tools")
import fitobj


def main():
    cl_obj, rva = sys.argv[1], int(sys.argv[2], 0)
    L = json.load(open("build/layout.json"))
    exe = open("FA/FA.EXE", "rb").read()
    cs = [c for c in L["text_chunks"] if c["rva"] == rva]
    fa = exe[cs[0]["off"]:cs[0]["off"] + cs[0]["size"]]
    secs, defs = fitobj.read_obj(cl_obj)
    text = next(s for s in secs if s["name"] == ".text")
    open("/tmp/w26c_cl.bin", "wb").write(bytes(text["content"]))
    rels = dict((r[0], r[1]) for r in text["relocs"])
    adj = 0
    print("== FA (%d B) vs CL (%d B), rels: %s" % (len(fa), len(text["content"]),
                                                   sorted(b for b, _ in rels.items())))
    for va, hexb, t in sites_objdump("/tmp/w26c_cl.bin", len(text["content"])):
        o = va
        rr = rels.get(o)
        mark = ""
        if rr:
            mark = "REL?%s" % rr
        print("CL  %04x  %-20s  %s" % (o, hexb, mark))
    print()
    for va, hexb, t in sites_objdump_fromFA(fa):
        print("FA  %04x  %-20s" % (va, hexb))


def sites_objdump(path, n):
    cmd = ["objdump", "-D", "-b", "binary", "-m", "i386", "-M", "intel",
           "--adjust-vma=0", path]
    out = subprocess.run(cmd, capture_output=True, text=True).stdout
    lines = []
    for ln in out.splitlines():
        s = ln.strip()
        if s and ":" in s and "file format" not in s and "section" not in s \
                and not s.startswith(">"):
            a, b = s.split(":", 1)
            try:
                va = int(a.strip(), 16)
            except ValueError:
                continue
            if va >= n:
                continue
            hb, tt = b.split("\t", 1) if "\t" in b else (b, "")
            lines.append((va, hb.strip(), tt.strip()))
    return lines


def sites_objdump_fromFA(fa):
    adj = 0x400c00
    open("/tmp/w26c_fa.bin", "wb").write(fa)
    cmd = ["objdump", "-D", "-b", "binary", "-m", "i386", "-M", "intel",
           "--adjust-vma=%#x" % adj, "--start-address=0", "--stop-address=%#x" % len(fa),
           "/tmp/w26c_fa.bin"]
    out = subprocess.run(cmd, capture_output=True, text=True).stdout
    lines = []
    for ln in out.splitlines():
        s = ln.strip()
        if s and ":" in s and "file format" not in s and "section" not in s \
                and not s.startswith(">"):
            a, b = s.split(":", 1)
            try:
                va = int(a.strip(), 16) - 0
            except ValueError:
                continue
            hb, tt = b.split("\t", 1) if "\t" in b else (b, "")
            lines.append((va, hb.strip(), tt.strip()))
    return lines


if __name__ == "__main__":
    main()