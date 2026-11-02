#!/usr/bin/env python3
"""Disassemble the .text of a CL (or fit) obj; w25a helper."""
import struct, subprocess, sys

p = sys.argv[1]
d = open(p, "rb").read()
(mach, nsec, ts, symptr, nsym, opthsz, chars) = struct.unpack_from("<HHIIIHH", d, 0)
off = 20 + opthsz
stro = symptr + nsym * 18
secs = []
for i in range(nsec):
    name = d[off:off+8].rstrip(b"\0").decode("latin-1")
    (vsz, va, rsz, rptr, relptr, lnptr, nrel, nln, flags) = struct.unpack_from("<IIIIIIHHI", d, off+8)
    secs.append(dict(name=name, rsz=rsz, rptr=rptr, relptr=relptr, nrel=nrel, va=va))
    off += 40

def sym(i):
    rec = symptr + i*18
    if d[rec:rec+4] == b"\0\0\0\0":
        o = stro + struct.unpack_from("<I", d, rec+4)[0]
        return d[o:d.index(b"\0", o)].decode("latin-1")
    return d[rec:rec+8].rstrip(b"\0").decode("latin-1")

syms = {}
n = 0
while n < nsym:
    rec = symptr + n*18
    if not d[rec+17] and d[rec+16] == 2:
        val, secnum = struct.unpack_from("<IH", d, rec+8)
        syms[(secnum, val)] = sym(n)
    n += 1 + d[rec+17]

for s in secs:
    if s["name"] != ".text": continue
    print("=== .text %d bytes, %d relocs ===" % (s["rsz"], s["nrel"]))
    rel = [(struct.unpack_from("<IIH", d, s["relptr"]+i*10)) for i in range(s["nrel"])]
    # object file symbol values are section-relative
    tmp = "/tmp/w25a_text.bin"
    open(tmp, "wb").write(d[s["rptr"]:s["rptr"]+s["rsz"]])
    import tempfile
    tf = "/tmp/w25a_text.diself"
    # wrap as PE-less disassembly via objdump with --adjust-vma
    out = subprocess.run(["objdump", "-D", "-b", "binary", "-m", "i386",
                          "--adjust-vma=0x401000", tmp, "--insn-width=8"],
                         capture_output=True, text=True).stdout
    lines = out.splitlines()
    cur = 0
    relmap = {}
    for (o, si, t) in rel:
        relmap[o] = (sym(si), t)
    for ln in lines:
        st = ln.find(":")
        if st > 0 and ln[st-8:st] and all(c in "0123456789abcdef" for c in ln[st-8:st]):
            try: a = int(ln[st-8:st], 16)
            except ValueError: a = None
            if a is not None:
                o = a - 0x401000
                if o in relmap:
                    n_, t = relmap[o]
                    ln = ln + "   ; @%#x %s %s" % (o, "DIR32" if t==6 else ("REL32" if t==20 else t), n_)
        print(ln)
