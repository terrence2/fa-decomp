#!/usr/bin/env python3
"""w25b helper: hexdump a CL obj's .text (and FA chunk) with reloc positions."""
import json, struct, sys

def secs(path):
    d = open(path, "rb").read()
    (mach, nsec, ts, symptr, nsym, opthsz, chars) = struct.unpack_from("<HHIIIHH", d, 0)
    off = 20 + opthsz
    out = []
    for i in range(nsec):
        name = d[off:off+8].rstrip(b"\0").decode()
        (vsz, va, rsz, rptr, relptr, lnptr, nrel, nln, flags) = struct.unpack_from("<IIIIIIHHI", d, off+8)
        out.append(dict(name=name, flags=flags, content=d[rptr:rptr+rsz], relptr=relptr, nrel=nrel))
        off += 40
    return d, out, symptr, nsym

def syms(d, symptr, nsym):
    stro = symptr + nsym * 18
    s, n = {}, 0
    while n < nsym:
        rec = d[symptr+n*18:symptr+n*18+18]
        if rec[:4] == b"\0\0\0\0":
            o = stro + struct.unpack_from("<I", rec, 4)[0]
            nm = d[o:d.index(b"\0", o)].decode()
        else:
            nm = rec[:8].rstrip(b"\0").decode()
        val, secnum = struct.unpack_from("<IH", rec, 8)
        cls, aux = rec[16], rec[17]
        s[nm] = (val, secnum, cls, aux)
        n += 1 + aux
    return s

if __name__ == "__main__":
    obj = sys.argv[1]
    d, ss, sp, ns = secs(obj)
    t = next(s for s in ss if s["name"] == ".text")
    print(".text %d bytes" % len(t["content"]))
    # relocs
    rels = []
    for i in range(t["nrel"]):
        o, symi, typ = struct.unpack_from("<IIH", d, t["relptr"]+i*10)
        rels.append((o, symi, typ))
    table = sys.argv[2] if len(sys.argv) > 2 else ""
    if table == "fa":
        L = json.load(open("build/layout.json"))
        c = next(c for c in L["text_chunks"] if c["rva"] == int(sys.argv[3]))
        exe = open("FA/FA.EXE", "rb").read()
        b = exe[c["off"]:c["off"]+c["size"]]
        print("FA chunk %s %d bytes" % (c["name"], len(b)))
        print(b.hex(" "))
        sys.exit(0)
    s = syms(d, sp, ns)
    names = {i: nm for nm, v in s.items() for i in [0] if False}
    symnames = list(s.keys())
    # index-based names need raw walk; rebuild:
    raw = []
    n = 0
    while n < ns:
        rec = d[sp+n*18:sp+n*18+18]
        if rec[:4] == b"\0\0\0\0":
            o = (sp+ns*18) + struct.unpack_from("<I", rec, 4)[0]
            nm = d[o:d.index(b"\0", o)].decode()
        else:
            nm = rec[:8].rstrip(b"\0").decode()
        raw.append((n, nm, struct.unpack_from("<IH", rec, 8), rec[16], rec[17]))
        n += 1 + rec[17]
    b = t["content"]
    relmap = {o: (raw[symi][1] if symi < len(raw) else "#%d" % symi, typ) for o, symi, typ in rels}
    for off in range(0, len(b), 16):
        row = b[off:off+16].hex(" ")
        marks = []
        for o in sorted(relmap):
            if off <= o < off+16:
                marks.append("%+d=%s(%d)" % (o, relmap[o][0], relmap[o][1]))
        print("%04x  %-47s  %s" % (off, row, " ".join(marks)))
    print("undefined externals (secnum 0 cls 2):")
    for i, nm, (val, secnum), cls, aux in raw:
        if secnum == 0 and cls == 2:
            print("  UNDEF:", nm)