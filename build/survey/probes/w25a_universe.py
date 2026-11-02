#!/usr/bin/env python3
"""W25A final external-universe check: list undefined externals (secnum==0,
cls==2) of a fit obj and verify each name exists in the FA universe."""
import json, struct, sys

FA = "/home/terrence/Projects/fa-decomp/FA"
def universe():
    L = json.load(open("/home/terrence/Projects/fa-decomp/build/layout.json"))
    u = set()
    for c in L["text_chunks"]:
        if c.get("name"): u.add(c["name"])
        u.add("$FA$_t_%06x" % (c["rva"] + 0x400000))
    for c in L["data_chunks"]:
        if c.get("name"): u.add(c["name"])
        u.add("$FA$_d_%06x" % (c["va"]))
    for s in L["syms"]:
        u.add(s[1])
    sms = json.load(open("/home/terrence/Projects/fa-decomp/fa_sms_map.json")) if False else None
    imp = L.get("imports") or []
    def walk(x):
        if isinstance(x, str): u.add(x)
        elif isinstance(x, dict):
            for v in x.values(): walk(v)
        elif isinstance(x, list):
            for v in x: walk(v)
    walk(imp)
    exp = L.get("exports") or []
    walk(exp)
    return u

def syms(path):
    d = open(path, "rb").read()
    if d[:2] != b"\x4c\x01": raise SystemExit("not i386 obj: " + path)
    (mach, nsec, ts, symptr, nsym, opthsz, chars) = struct.unpack_from("<HHIIIHH", d, 0)
    off = 20 + opthsz
    stro = symptr + nsym * 18
    out = []
    n = 0
    while n < nsym:
        rec = symptr + n * 18
        if d[rec:rec+4] == b"\0\0\0\0":
            o = stro + struct.unpack_from("<I", d, rec+4)[0]
            name = d[o:d.index(b"\0", o)].decode("latin-1")
        else:
            name = d[rec:rec+8].rstrip(b"\0").decode("latin-1")
        aux = d[rec+17]
        val, secnum = struct.unpack_from("<IH", d, rec+8)
        typ = struct.unpack_from("<H", d, rec+14)[0]
        cls = d[rec+16]
        if cls == 2 and secnum == 0:
            out.append(name)
        n += 1 + aux
    return out, set(out)

if __name__ == "__main__":
    u = universe()
    ok = True
    for p in sys.argv[1:]:
        ud, ss = syms(p)
        bad = [s for s in ss if s not in u]
        print(p, "%d undefs" % len(ud))
        for s in ud:
            print("   ", s, "OK" if s in u else "*** MISSING ***")
        if bad: ok = False
    sys.exit(0 if ok else 1)
