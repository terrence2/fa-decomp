#!/usr/bin/env python3
"""Shared site enumeration for decompilation tooling (dis.py, mapgen.py).

chunk_sites() lists every relocation a fitted CL object will carry for a
chunk, with the FA-side truth: absolute fixups from build/reloc_map.json
(base relocs only carry absolute dwords -- call/jmp REL32 sites are NOT in
it, they come from objdump's decoded instruction stream) and REL32 sites
from objdump lines, each resolved to an anchor symbol + addend via
tools/anchors.py.  Anchors alias: any (symbol, addend) covering the same
resolved VA is equivalent, so "same map" means same VA, never same string.

Map-semantics note (fitobj): DIR32 final = sym + content; REL32 final =
sym + content - (site+4).  A `TO+addend` map bakes the addend into the
site's content dword, so TO+delta reproduces the FA value.
"""
import bisect
import json
import re
import struct
import subprocess

IMAGE_BASE = 0x400000

# objdump line: "  49b201:\te8 ea 00 00 00 \tcall   0x49b2f0"
LINE_RE = re.compile(r"^\s*([0-9a-f]+):\s+(?:([0-9a-f ]+?)\s{2,})\t(.*)$")


def load_layout():
    return json.load(open("build/layout.json"))


def load_reloc_map():
    return json.load(open("build/reloc_map.json"))


def load_exe():
    return open("FA/FA.EXE", "rb").read()


def find_chunk(arg, L, sec="text"):
    """rva|VA|name -> chunk dict (text_chunks or data_chunks)."""
    key = "text_chunks" if sec == "text" else "data_chunks"
    chunks = L[key]
    a = arg.strip()
    try:
        n = int(a, 0)
    except ValueError:
        named = [c for c in chunks if c.get("name") == a]
        if len(named) == 1:
            return named[0]
        raise SystemExit("no unique %s chunk named %r" % (sec, a))
    if a.startswith("0x") and n < IMAGE_BASE:
        pass  # rva form
    elif n >= IMAGE_BASE:
        n -= IMAGE_BASE  # VA form
    for c in chunks:
        if c["rva"] <= n < c["rva"] + c.get("size", c.get("size_full", 0)):
            return c
    raise SystemExit("no %s chunk covers %s" % (sec, a))


def fpo_decode(c):
    """Decode the 16-byte FPO record (layout hex string) -> dict or None."""
    if not c.get("fpo_rec"):
        return None
    off_start, cbproc, locals_, params, flags = struct.unpack(
        "<IIIHH", bytes.fromhex(c["fpo_rec"]))
    return dict(offStart=off_start, cbProcSize=cbproc, cdwLocals=locals_,
                cdwParams=params, cbProlog=flags & 0xff,
                cbRegs=(flags >> 8) & 7, fHasSEH=(flags >> 11) & 1,
                fUseBP=(flags >> 12) & 1, cbFrame=(flags >> 13) & 3,
                frame=("ebp" if (flags >> 12) & 1 else "fpo/esp"))


def objdump_range(start_va, end_va, exe_path="FA/FA.EXE"):
    """Disassemble [start_va, end_va) via the whole-file adjust-vma trick
    (no temp files).  Returns the list of parsed instruction lines:
    (addr, bytes_hex, text)."""
    adj = 0
    try:
        # adjust = va(at file offset 0x1000 base = rawptr 0x400): we need the
        # VMA of FILE offset 0 to be start_va - off(start), so map off->va:
        # simplest correct choice: adj = start_va is wrong; compute from any
        # layout chunk instead.
        L = load_layout()
        c = min(L["text_chunks"], key=lambda c: c["off"])
        adj = c["va"] - c["off"]        # constant across all chunks
    except Exception:
        adj = IMAGE_BASE
    cmd = ["objdump", "-D", "-b", "binary", "-m", "i386", "-M", "intel",
           "--adjust-vma=%#x" % adj,
           "--start-address=%#x" % start_va, "--stop-address=%#x" % end_va,
           exe_path]
    out = subprocess.run(cmd, capture_output=True, text=True).stdout
    lines = []
    for ln in out.splitlines():
        m = LINE_RE.match(ln)
        if m:
            lines.append((int(m.group(1), 16), m.group(2), m.group(3)))
    return lines


def _describe(tgt, anc, chunk, span_end=None):
    """(anchor_name, addend, is_self, note) for an absolute VA target."""
    base_end = span_end if span_end is not None else \
        chunk["va"] + chunk["size"]
    is_self = chunk["va"] <= tgt < base_end
    if anc is None:
        return ("", 0, is_self, "unresolved")
    name, symva = anc
    return (name, tgt - symva, is_self,
            "$FA$-gap+delta" if name.startswith("$FA$_") else "")


def suggest_from(name, addend, tgt, kind):
    """(from_suggestion_or_None, label) -- the FROM taxonomy.  FROM names are
    inherently C-side choices; these are heuristics, always labelled."""
    if kind == "rel32":
        if name.startswith("?"):
            return None, "human confirm"
        if addend:
            return None, "human-coin"
        if name.startswith(("_", "@")):
            return (name if name.startswith("@") else name), "identity"
        return None, "human confirm"
    # data site
    if name.startswith("$FA$rdata0"):
        return None, "human-coin (rdata literal)"
    if name.startswith("$FA$iat"):
        return None, "human-coin (IAT ordinal)"
    if name.startswith("__imp__"):
        return "FROM=TO identity", "identity"
    if addend:
        return None, "human-coin (interior/field offset)"
    if name.startswith("$FA$_"):
        return None, "human-coin (gap anchor)"
    if name.startswith("?"):
        return "_<bare>=<anchor>", "human confirm"
    if name.startswith(("_", "@")):
        return name, "identity"
    return None, "human confirm"


def chunk_sites(L, rm, exe, chunk, span=None):
    """Enumerate every reloc a fitted CL obj will carry.

    span: (rva_start, size) tiles consecutive chunks like fitobj --span
    (fixups/rel32s get span-relative offsets; the host chunk is the span
    union).  Returns {abs_fixups, rel32s, aliases, span_chunks}."""
    if span is not None:
        r0, sz = span
        cs = [c for c in L["text_chunks"] if r0 <= c["rva"] < r0 + sz]
        assert cs[0]["rva"] == r0, "span must start on a chunk boundary"
        assert sum(c["size"] for c in cs) == sz, \
            "span chunks do not tile [rva, rva+%#x)" % sz
    else:
        r0 = chunk["rva"]
        cs = [chunk]
    base = r0 + IMAGE_BASE
    span_end = base + sz if span is not None else base + chunk["size"]
    anc = None
    import anchors
    anc = anchors.Anchors(L)

    # ---- absolute fixups (reloc_map, keyed by decimal-string abs VA) ----
    abs_fixups = []
    for c in cs:
        for o in rm["text"].get(str(c["va"]), []):
            off = int(o) + (c["rva"] - r0)
            fo = c["off"] + int(o)
            tgt, = struct.unpack_from("<I", exe, fo)
            a = _describe(tgt, anc.anchor(tgt), cs[0], span_end)
            kind_class = ("IAT" if a[0].startswith("__imp__") or
                          a[0].startswith("$FA$iat") else "abs")
            abs_fixups.append(dict(off=off, kind="abs", cls=kind_class,
                                   tgt=tgt, anchor=a[0], addend=a[1],
                                   is_self=a[2], note=a[3]))

    # ---- rel32 call/jmp sites from objdump (never a raw byte scan) ----
    lines = objdump_range(base, span_end)
    rel32s = []
    for va, hexb, text in lines:
        m = re.match(r"^(call|jmp)\s+0x([0-9a-f]+)\s*$", text)
        if not m:
            continue
        op, t = m.group(1), int(m.group(2), 16)
        if not (IMAGE_BASE <= t < IMAGE_BASE + 0xf0000):  # in-image target
            continue
        o = va - base
        a = _describe(t, anc.anchor(t), cs[0], span_end)
        rel32s.append(dict(off=o, kind="rel32", op=op, tgt=t, anchor=a[0],
                           addend=a[1], is_self=a[2], note=a[3],
                           nbytes=len(hexb.split()) if hexb else 5))

    # ---- span aliases (inner chunks must be re-definable offsets) ----
    aliases = []
    if span is not None:
        for c in cs[1:]:
            nm = c["name"] or "$FA$_t_%06x" % c["va"]
            aliases.append("%#x=%s" % (c["va"] - base, nm))

    return dict(abs_fixups=abs_fixups, rel32s=rel32s, aliases=aliases,
                span_chunks=cs, chunk=cs[0],
                size=sz if span else chunk["size"], rva=r0,
                _L=L, _rm=rm, _exe=exe)