#!/usr/bin/env python3
"""Byte-level diagnosis of idirect.exe vs FA (vsz-limited, region diffs)."""
import struct, json, sys

def parse_pe(path):
    d = open(path, "rb").read()
    e, = struct.unpack_from("<I", d, 0x3C)
    mach, nsec, ts, symptr, nsym, ohs, ch = struct.unpack_from("<HHIIIHH", d, e+4)
    opt = e + 4 + 20
    secs = []
    sp = opt + ohs
    for i in range(nsec):
        nm = d[sp:sp+8].rstrip(b"\0").decode(errors="replace")
        vsz, va, rsz, rptr, relp, lnnp, nrel, nln, fl = struct.unpack_from("<IIIIIIHHI", d, sp+8)
        secs.append(dict(name=nm, vsz=vsz, va=va, rsz=rsz, rptr=rptr, flags=fl))
        sp += 40
    return d, secs, opt

fa_d, fa_secs, fa_opt = parse_pe("FA/FA.EXE")
id_d, id_secs, id_opt = parse_pe("build/m0/idirect.exe")

print("idirect.exe sections:")
for s in id_secs:
    print("  %-8s va=0x%-5x vsz=0x%-6x rsz=0x%-6x rptr=0x%-6x flags=0x%08x" %
          (s["name"], s["va"], s["vsz"], s["rsz"], s["rptr"], s["flags"]))

print("FA sections:")
for s in fa_secs:
    print("  %-8s va=0x%-5x vsz=0x%-6x rsz=0x%-6x rptr=0x%-6x flags=0x%08x" %
          (s["name"], s["va"], s["vsz"], s["rsz"], s["rptr"], s["flags"]))

def dd(d, opt, n):
    return struct.unpack_from("<II", d, opt + 96 + n*8)

for label, d, opt in (("FA", fa_d, fa_opt), ("ID", id_d, id_opt)):
    print(label + " data dirs (n=15):")
    for i in range(15):
        rva, sz = dd(d, opt, i)
        if rva:
            print("   [%d] rva=0x%-6x size=0x%-5x" % (i, rva, sz))

# .idata content comparison, limited to min vsz slice
idl = [s for s in id_secs if s["name"] == ".idata"]
print(".idata occurrences in idirect:", len(idl))
s_id = idl[0]
s_fa = next(s for s in fa_secs if s["name"] == ".idata")
a = id_d[s_id["rptr"]:s_id["rptr"]+s_id["rsz"]]
b = fa_d[s_fa["rptr"]:s_fa["rptr"]+s_fa["rsz"]]
n = min(len(a), len(b), s_id["vsz"] if s_id["vsz"] else len(a))
# in a section with vsz < rsz, valid content = rsz but meaningful = vsz.. actually FA .idata rawsz?
print("FA .idata rawsz=0x%x, idirect rawsz=0x%x, idirect vsz=0x%x" % (s_fa["rsz"], s_id["rsz"], s_id["vsz"]))
a2 = a[:len(b)]
if a2 == b:
    print("MATCH: first 0x%x bytes identical" % len(b))
else:
    # region diff
    regions = []
    start = None
    for i in range(len(b)):
        if i < len(a2) and a2[i] == b[i]:
            if start is not None:
                regions.append((start, i)); start = None
        else:
            if start is None:
                start = i
    if start is not None:
        regions.append((start, len(b)))
    print("%d differing regions" % len(regions))
    for (st, en) in regions[:20]:
        print("  diff 0x%04x-0x%04x" % (st, en))
        print("    id: %s" % a2[st:min(en, st+32)].hex())
        print("    fa: %s" % b[st:min(en, st+32)].hex())
