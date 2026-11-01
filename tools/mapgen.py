#!/usr/bin/env python3
"""Emit the fitobj `maps:` (and span `aliases:`) lines a pilot would have
had to derive by hand, from the FA-side truth in tools/sites.py.

Usage:
  python3 tools/mapgen.py <rva|name> [--span 0xSIZE] [--maps] [--json]

Contract: the tool GUARANTEES target VA, anchor symbol, addend, site
offset and relocation class; it CANNOT know the CL object's symbol names
(FROMs depend on what the C author declared).  Every suggested line is
labelled:
  [identity]      anchor looks like a plain C symbol; a C extern of the
                  same name needs no map line at all (link resolves it)
  [human confirm] mangled FA.SMS name, addend 0: C extern + `FROM=TO` map
  [human-coin]    interior/field/rdata/IAT-ordinal target: C author must
                  name the placeholder, addend is authoritative
  [CL-internal]   CL-only names ($T... scope tables) map to `$FA$rdata0+`
Validation of any regenerated entry is RESOLVED-VA equivalence -- anchors
alias, string differences that resolve to the same VA are fine.
"""
import re
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0])
import sites  # noqa: E402
import dis as dismod  # noqa: E402  (dis.py: header/printing helpers)


def mangle_bare(name):
    """Plausible C-side bare name from a mangled FA.SMS symbol."""
    m = re.match(r"\?([A-Za-z_][A-Za-z0-9_]*)@@.*@@3", name)
    if m:
        return "_" + m.group(1)
    m = re.match(r"\?([A-Za-z_][A-Za-z0-9_]*)@@.*@@Y", name)
    if m:
        return m.group(1)
    return None


def suggested_maps(s):
    """Grouped suggested maps: one entry per distinct (anchor, label) with
    the set of addends.  Returns list of dict(anchor, addends, label)."""
    groups = {}
    for f in s["abs_fixups"] + s["rel32s"]:
        if f["is_self"]:
            continue
        sug, label = sites.suggest_from(f["anchor"], f["addend"], f["tgt"],
                                        f["kind"])
        key = f["anchor"]
        g = groups.setdefault(key, dict(anchor=key, addends=[], label=label,
                                        sites=[]))
        if f["addend"] not in g["addends"]:
            g["addends"].append(f["addend"])
        g["sites"].append(f)
    return list(groups.values())


def render_maps(groups):
    out = []
    for g in sorted(groups, key=lambda x: x["label"], reverse=True):
        a = g["anchor"]
        adds = sorted(g["addends"]) or [0]
        # CL bakes struct-field displacements into its OWN content dwords,
        # so ONE map at the anchor (or min addend) usually covers all
        # sites; the C side decides.  Emit the natural-anchor form +
        # the addend set as a comment.
        use = min(adds)
        tgt = a + ("+0x%x" % use if use else "")
        if g["label"] == "identity":
            out.append('    "%s=%s",  # [identity]: a plain extern of this '
                       'name needs NO map' % (a, a))
        elif a.startswith("?"):
            bare = mangle_bare(a)
            frm = bare or "_TODO"
            out.append('    "%s=%s",  # [human confirm]' % (frm, tgt))
        else:
            out.append('    "_TODO=%s",  # [%s]' % (tgt, g["label"]))
        if len(adds) > 1:
            out.append("    # addends seen: %s (one map may cover all if CL "
                       "bakes field disp into its content)"
                       % ", ".join("+0x%x" % x for x in adds))
    return out


def main():
    argv = []
    flags = {}
    args = sys.argv[1:]
    i = 0
    while i < len(args):
        if args[i] == "--span":
            flags["span"] = int(args[i + 1], 0)
            i += 2
        elif args[i] in ("--maps", "--json"):
            flags["maps_only"] = args[i] == "--maps"
            i += 1
        else:
            argv.append(args[i])
            i += 1
    L = sites.load_layout()
    rm = sites.load_reloc_map()
    exe = sites.load_exe()
    chunk = sites.find_chunk(argv[0], L)
    span = (chunk["rva"], flags["span"]) if flags.get("span") else None
    s = sites.chunk_sites(L, rm, exe, chunk, span)
    c = s["chunk"]
    groups = suggested_maps(s)
    hdr = ["== chunk %s @ rva %#x va %#08x size %#x"
           % (c["name"] or "(unnamed)", c["rva"], c["va"], s["size"])]
    d = sites.fpo_decode(c)
    hdr.append(dismod.fpo_line(c))
    for ln in hdr:
        print(ln)
    if flags.get("maps_only"):
        print('"maps": [')
        for ln in render_maps(groups):
            print(ln)
        print(']')
        if s["aliases"]:
            print('"aliases": [%s],' %
                  ", ".join('"%s"' % a for a in s["aliases"]))
        return
    print("---- site table ----")
    all_groups = suggested_maps(s)
    for f in s["abs_fixups"]:
        add = "+0x%x" % f["addend"] if f["addend"] else ""
        g = next((g for g in all_groups if g["anchor"] == f["anchor"]), None)
        label = g["label"] if g else "self"
        print("  abs @%#02x -> %-30s %-4s [%s]" % (f["off"],
                                                   f["anchor"] + add,
                                                   f["cls"], label))
    for r in s["rel32s"]:
        add = "+0x%x" % r["addend"] if r["addend"] else ""
        g = next((g for g in all_groups if g["anchor"] == r["anchor"]), None)
        label = g["label"] if g else "self"
        print("  rel @%#02x %-4s -> %-30s [%s]" % (r["off"], r["op"],
                                                   r["anchor"] + add, label))
    if s["aliases"]:
        print("---- span aliases ----")
        for a in s["aliases"]:
            print('  "%s",' % a)
    print("---- human decisions needed ----")
    for g in suggested_maps(s):
        if g["label"] == "identity":
            continue
        adds = ", ".join("+0x%x" % x for x in sorted(g["addends"]) or [0])
        print("  %-14s %s (%s)" % (g["label"], g["anchor"], adds))


if __name__ == "__main__":
    main()