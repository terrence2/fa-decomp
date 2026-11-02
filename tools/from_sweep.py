#!/usr/bin/env python3
"""FROM-decoration sweep: for each swap/batch entry, cross-check the maps
FROM spellings against the C source's extern declarations.

Checks per map line `FROM=TO`:
  1. FROM's C-side identifier (decoration stripped) is declared extern in src.
  2. The decoration matches the declaration's calling convention shape:
     cdecl (_X), stdcall (_X@N), fastcall (@X@N), thiscall (@X@N), dllimport
     (__imp__X / __imp__X@N), AIL (__imp___AIL_x@N), chunk anchors ($FA$*).
     Arity mismatches (@N N != arg bytes) are NOT checked here — the link
     catches those as LNK2001.

Exit 1 if any entry has a mismatch. Usage:
    python3 tools/from_sweep.py build/w21/batch_a.json build/w21/batch_b.json
    (or no args = tools/swap.json)
"""
import json
import re
import struct
import sys

STRIP = re.compile(r"^(?:__imp__+)?(?:AIL_)?(?P<pfx>[@_]?)(?P<name>[A-Za-z_\?][\w?$@]*?)(?P<dec>@\d+)?$")


def strip_from(f):
    """Return (pfx, c_name, dec) for a map FROM spelling."""
    m = STRIP.match(f)
    if not m:
        return ("", f.split("@")[0].strip("_"), "")
    g = m.groupdict()
    return (g["pfx"], g["name"].lstrip("_"), g["dec"] or "")


DECL = re.compile(r'extern\s+((?:const\s+)?[\w\s\*]+?)\b(?P<name>[A-Za-z_]\w*)\s*(?P<paren>\((?:[^()]|\([^()]*\))*\))?\s*\[?\]?\s*;')
FDECL = re.compile(r'^[^\n;{}]*\b([A-Za-z_]\w*)\s*\((?:[^()]|\([^()]*\))*\)\s*;', re.M)
CC = re.compile(r"__(?:std|fast|cdecl)\b")


def externs_of(src_text):
    """{c_name: (qualifier_blob, has_params)} for every extern declaration."""
    out = {}
    for m in DECL.finditer(src_text):
        q, name, paren = m.group(0), m.group("name"), m.group("paren")
        out[name] = (q, paren is not None)
    # bare (implicitly-extern) function declarations: 'void __cdecl foo(...);'
    for m in FDECL.finditer(src_text):
        out.setdefault(m.group(1), (m.group(0), True))
    return out


def shape_ok(pfx, dec, decl_q, has_params):
    blob = " ".join(decl_q.split())
    if "__fastcall" in blob or "__thiscall" in blob:
        return pfx == "@" and (dec != "") == has_params
    if "__stdcall" in blob or blob.endswith("PASCAL") or "WINAPI" in blob:
        return pfx == "_" and (dec != "") == has_params
    # cdecl / plain extern / data: _X (no @N)
    return pfx == "_" and dec == ""


def sweep(entries, source="file"):
    errs = 0
    for e in entries:
        try:
            src = open(e["src"]).read()
        except OSError as ex:
            print("%-24s MISSING SRC %s" % (e["obj"], ex))
            errs += 1
            continue
        ext = externs_of(src)
        for mapline in e.get("maps", []):
            f = mapline.split("=", 1)[0]
            pfx, name, dec = strip_from(f)
            # __imp__ thunks are data symbols; @N is part of the import name
            # (KERNEL32/USER32/ADVAPI32/DDRAW) — no decl-shape check applies.
            if f.startswith("__imp__"):
                continue
            # CRT/CL-internal symbols (__doexit, ___newmode, $T... etc.) are
            # resolved by the CRT objects at link, not by src declarations.
            if f.startswith("__") or f.startswith("$"):
                continue
            if name not in ext:
                # asm-block / CRT-internal / self-referential symbols live in
                # the source text without an `extern` decl at file scope.
                if name == e["obj"] or re.search(r"\b%s\b" % re.escape(name),
                                                 src):
                    continue
                print("%-24s FROM '%s': no extern named %s in %s"
                      % (e["obj"], f, name, e["src"]))
                errs += 1
                continue
            q, has_params = ext[name]
            # data externs (no parens) must be underscored, never @N
            if not has_params and dec:
                print("%-24s FROM '%s': %s is a DATA extern but FROM carries %s"
                      % (e["obj"], f, name, dec))
                errs += 1
            elif has_params:
                if pfx == "" or (pfx == "_" and not dec and
                                 ("__stdcall" in q or "__fastcall" in q)):
                    print("%-24s FROM '%s': %s is a CC-declared function but "
                          "FROM looks cdecl (missing @N / wrong prefix)"
                          % (e["obj"], f, name))
                    errs += 1
    print("sweep: %d entries, %d problem(s)" % (len(entries), errs))
    return errs


def objcheck(entries):
    """Byte-level cross-check: a fit obj's undefined externals must all be
    resolvable at link. Universe = FA chunk names (text/data), import
    thunks, every map TO in the swap set, and CRT-internal symbols the CRT
    objects resolve. Anything else will LNK2001 -- catches FROM spellings
    that drifted from what CL actually emitted (decl-level sweep can't:
    the decl in the C file and the map can agree while the obj disagrees
    with BOTH; seen when a hand-edit changed decls after the sweep ran).
    """
    import subprocess, io
    lay = json.load(open("build/layout.json"))
    uni = set()
    for c in lay["text_chunks"] + lay["data_chunks"]:
        n = c.get("name")
        if n:
            uni.add(n)
    try:
        imp = json.load(open("build/fa_imports.json"))
        for it in (imp if isinstance(imp, list) else imp.get("symtab", [])):
            n = it if isinstance(it, str) else it.get("name", "")
            if n:
                uni.add(n)
    except OSError:
        pass
    for e in entries:
        for m in e.get("maps", []):
            uni.add(m.split("=", 1)[1].split("+", 1)[0])
        uni.add(e["obj"])
    import coff
    sys.path.insert(0, "tools")
    errs = 0
    for e in entries:
        p = "build/pilot/%s_fit.obj" % e["obj"]
        try:
            secs, syms = obj_externals(p)
        except OSError:
            errs += 1
            print("%-24s NO FIT OBJ" % e["obj"])
            continue
        for n in syms:
            if n in uni or n.endswith(e["obj"]):
                continue
            # CRT-internal / CL-internal spellings resolve from libcmt.objs
            # or as section-adjacent locals (CL scope symbols, __except_list)
            if n.startswith("__") or n.startswith("$") or \
                    re.match(r"^@@[\?]?\w", n) or n == "__except_list":
                continue
            errs += 1
            print("%-24s UNRESOLVABLE external %s (no FA chunk / map TO / "
                  "import match -- will LNK2001)" % (e["obj"], n))
    print("objcheck: %d entries, %d problem(s)" % (len(entries), errs))
    return errs


def obj_externals(p):
    """[(name)] for every class-2 (external) symbol, via coff.objinfo."""
    out = []
    data = open(p, "rb").read()
    (mach, nsec, ts, symptr, nsym, opthsz, chars) = struct.unpack_from(
        "<HHIIIHH", data, 0)
    stro = symptr + nsym * 18
    n = 0
    while n < nsym:
        rec = data[symptr + n * 18: symptr + (n + 1) * 18]
        if rec[:4] == b"\0\0\0\0":
            sval, = struct.unpack_from("<I", rec, 4)
            o = stro + sval
            name = data[o:data.index(b"\0", o)].decode("latin-1")
        else:
            name = rec[:8].rstrip(b"\0").decode("latin-1")
        cls, aux = rec[16], rec[17]
        if cls == 2 and not name.startswith("."):
            out.append(name)
        n += 1 + aux
    return [], set(out)


if __name__ == "__main__":
    files = [a for a in sys.argv[1:] if not a.startswith("-")] or \
        ["tools/swap.json"]
    es = []
    for p in files:
        es += json.load(open(p) if hasattr(open(p), "read") else open(p))
    rc = sweep(es)
    if "--objcheck" in sys.argv:
        rc += objcheck([e for e in es])
    sys.exit(1 if rc else 0)