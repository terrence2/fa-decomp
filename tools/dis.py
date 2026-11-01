#!/usr/bin/env python3
"""Annotated disassembly of an FA text chunk -- the bulk-decompilation
"understand" step in ONE command (replaces the /tmp slice + objdump + hand
annotation of the pilot era).

Usage:
  python3 tools/dis.py <rva|name> [len] [--span 0xSIZE] [--json]

Output: chunk header (FA.SMS name, FPO decode, filler-tail census), the
objdump listing with right-hand annotations (targets resolved via
tools/anchors.py from OUR tables -- unresolvable operands print `; ?`, never
a guessed name), then the site table (the maps preview).  `--span 0xSIZE`
tiles consecutive chunks like fitobj --span.  `--json` emits machine form
for scripted consumers (select.py --rva).

Pilot invariant: on the 7 done chunks this reproduces the "FA asm" blocks
recorded in the src/*.c headers.
"""
import re
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0])
import anchors  # noqa: E402
import padcensus  # noqa: E402
import sites  # noqa: E402


def annotate(chunk, s, span_start_va):
    """objdump lines with right-hand site annotations."""
    L, rm, exe = s["_L"], s["_rm"], s["_exe"]
    anc = anchors.Anchors(L)
    fix_by_off = {f["off"]: f for f in s["abs_fixups"]}
    rel_by_off = {r["off"]: r for r in s["rel32s"]}
    fix_offs = sorted(fix_by_off)
    adj_runs, run = [], []
    for o in fix_offs:
        if run and o != run[-1] + 4:
            adj_runs.append(run)
            run = []
        run.append(o)
    if run:
        adj_runs.append(run)
    table_offs = set()
    for r in adj_runs:
        if len(r) >= 2:
            table_offs.update(r)
    csz = s["size"]
    lines = sites.objdump_range(span_start_va, span_start_va + csz)
    out = []
    for va, hexb, text in lines:
        off = va - span_start_va
        ann = []
        rel = rel_by_off.get(off)
        if rel is not None:
            if rel["anchor"]:
                add = ("+0x%x" % rel["addend"]) if rel["addend"] else ""
                tag = "self" if rel["is_self"] else "ext"
                ann.append("-> %s%s (%s %s)" % (rel["anchor"], add, tag,
                                                rel["op"]))
            else:
                ann.append("-> ? (%s target %#x)" % (rel["op"], rel["tgt"]))
        f = fix_by_off.get(off)
        if f is not None:
            ann.append("[fixup %#02x abs]" % off)
        # absolute data reference rendered by objdump (ds:0x...) that is not
        # a base-reloc site: resolve for readability
        m = re.search(r"ds:0x([0-9a-f]+)", text)
        if m and f is None:
            t = int(m.group(1), 16)
            a = anc.anchor(t)
            if a and a[1] != t:
                ann.append("-> %s+0x%x" % (a[0], t - a[1]))
            elif a:
                ann.append("-> %s" % a[0])
        if off in table_offs:
            ann.append("table region")
        out.append((va, hexb, text, "; ".join(ann)))
    return out


def fpo_line(c):
    d = sites.fpo_decode(c)
    if d is None:
        return "FPO: none (gap chunk -- no .debug$F)"
    return ("FPO: offStart=%#x cbProcSize=%#x locals=%d dwords params=%d "
            "dwords cbProlog=%d cbRegs=%d SEH=%d frame=%s"
            % (d["offStart"], d["cbProcSize"], d["cdwLocals"], d["cdwParams"],
               d["cbProlog"], d["cbRegs"], d["fHasSEH"], d["frame"]))


def pad_line(c, exe):
    data = exe[c["off"]:c["off"] + c["size"]]
    if c["size"] % 16:
        return None
    for Ln in range(min(15, c["size"]), 0, -1):
        comp = padcensus.composition(data[-Ln:])
        if comp is not None:
            return "tail pad: %s (%d B)" % ("+".join(comp), Ln)
    return "tail pad: none (16-aligned, code-only end)"


def site_table(s):
    out = ["---- sites (fitobj preview) ----"]
    ext = [f for f in s["abs_fixups"] if not f["is_self"]]
    if ext:
        for f in ext:
            add = "+0x%x" % f["addend"] if f["addend"] else ""
            sug, label = sites.suggest_from(f["anchor"], f["addend"],
                                            f["tgt"], f["kind"])
            out.append("  abs @%#02x -> %-30s %-6s  [%s]%s"
                       % (f["off"], f["anchor"] + add, f["cls"], label,
                          "" if not sug else "  e.g. %s=?%s" % (sug, sug)))
    if s["rel32s"]:
        for r in s["rel32s"]:
            add = "+0x%x" % r["addend"] if r["addend"] else ""
            if r["is_self"]:
                out.append("  rel @%#02x %s -> self+%#x"
                           % (r["off"], r["op"], r["tgt"] - s["chunk"]["va"]))
            else:
                out.append("  rel @%#02x %s -> %s%s"
                           % (r["off"], r["op"], r["anchor"], add))
    if s["aliases"]:
        out.append("  aliases: %s" % " ".join(s["aliases"]))
    return out


def main():
    argv = sys.argv[1:]
    span = json_mode = None
    i = 0
    while i < len(argv):
        if argv[i] == "--span":
            span = (None, int(argv[i + 1], 0))
            i += 2
        elif argv[i] == "--json":
            json_mode = True
            i += 1
        else:
            arg = argv[i]
            i += 1
    L = sites.load_layout()
    rm = sites.load_reloc_map()
    exe = sites.load_exe()
    chunk = sites.find_chunk(arg, L)
    if span:
        span = (chunk["rva"], span[1])
    s = sites.chunk_sites(L, rm, exe, chunk, span)
    c = s["chunk"]
    print("== chunk %s @ rva %#x va %#08x size %#x (%d B)"
          % (c["name"] or "(unnamed)", c["rva"], c["va"], c["size"],
             c["size"]))
    print(fpo_line(c))
    pl = pad_line(c, exe)
    if pl:
        print(pl)
    lines = annotate(chunk, s, c["va"])
    print("---- disassembly ----")
    for va, hexb, text, ann in lines:
        print("%#08x: %-22s %-40s%s" %
              (va, hexb, text, ("  ; " + ann) if ann else ""))
    for ln in site_table(s):
        print(ln)


if __name__ == "__main__":
    main()