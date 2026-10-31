#!/usr/bin/env python3
"""Parse FA.EXE's .rsrc into a full resource tree (dirs, names, leaf data).

.rsrc: RVA 0x18c000, file 0x11c400, 0x1200 bytes. Directory subtree offsets
are .rsrc-internal; DataEntry data RVAs are full image RVAs.
"""
import struct
import sys

RVA, RAW, SZ = 0x18c000, 0x11c400, 0x1200
TYPES = {1: "CURSOR", 2: "BITMAP", 3: "ICON", 4: "MENU", 5: "DIALOG",
         6: "STRING", 12: "GROUP_CURSOR", 14: "GROUP_ICON", 16: "VERSION",
         24: "MANIFEST", 23: "HTML"}


def parse_rsrc(exe, rva=RVA, raw=RAW, size=SZ):
    def fi(r):     # internal offset -> file
        return raw + r

    def ident(nm):
        if nm & 0x80000000:
            so = nm & 0x7fffffff
            ln, = struct.unpack_from("<H", exe, fi(so))
            return ("name", exe[fi(so) + 2:fi(so) + 2 + ln * 2].decode("utf-16-le"))
        return ("id", nm)

    seen = {}

    def rdir(off, level):
        chars, ts, ver, nnid, nne = struct.unpack_from("<IIIHH", exe, fi(off))
        out = []
        for i in range(nnid + nne):
            nm, off2 = struct.unpack_from("<II", exe, fi(off + 16 + 8 * i))
            idt = ident(nm)
            if off2 & 0x80000000:
                out.append((idt, rdir(off2 & 0x7fffffff, level + 1)))
            else:
                drva, dsz, cp, cpg = struct.unpack_from("<IIII", exe, fi(off2))
                if off2 in seen:
                    print("WARN: data entry reuse off=%x" % off2, file=sys.stderr)
                seen[off2] = True
                blob = exe[fi(drva - rva):fi(drva - rva) + dsz]
                out.append((idt, ("leaf", blob, drva, dsz, cp, cpg)))
        return out

    return rdir(0, 0), seen


def main():
    exe = open("FA/FA.EXE", "rb").read()
    tree, seen = parse_rsrc(exe)

    def walk(node, path):
        for t, sub in node:
            if sub[0] == "leaf":
                lvl = [repr(x[1]) if x[0] == "name" else str(x[1]) for x in path]
                print("depth=%d %s size=0x%x (rva %x) lang=%s"
                      % (len(path), " / ".join(
                          (TYPES.get(path[0][1], "?") if i == 0 else lvl[i])
                          for i in range(len(path))), sub[3], sub[2],
                          lvl[2] if len(path) > 2 else "-"))
                if len(path) < 3:
                    print("   ^ shorter than 3 levels!")
            else:
                walk(sub, path + [t])

    walk(tree, [])
    print("data entries referenced:", len(seen))


if __name__ == "__main__":
    main()