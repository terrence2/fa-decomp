#!/usr/bin/env python3
"""Regroup the chunked swap set into per-TU entries (bridge-first pipeline).

The .text census is complete (3,832 chunk entries, tools/swap.json); this
tool regroups them into per-TU span entries driven by the calibrated TU map
(build/survey/tu_map.json), in stages:

  plan      Reads tools/swap.json + tu_map.json + layout.json, builds the
            1,408 units (TUs coalesced across span-entry boundaries; inter-TU
            pad chunks fall to the covering unit), emits src/tu/<tag>.c
            concatenations and the staging config tools/swap.tu.json with
            one "bridge": true entry per multi-row unit (single-row units
            keep their proven per-chunk entries verbatim).
  bridge    Builds each multi-row unit's fit obj DIRECTLY from FA/FA.EXE
            bytes (the fitobj span path's exact emit, minus the CL obj):
            content = FA chunk bytes over the unit span, stub fixup relocs
            (Anchors + reloc_map, addend-baked), per-chunk .debug$F, main
            symbol = first chunk anchor, aliases for interior chunk anchors.
            Written to build/pilot/<obj>_fit.obj; swap.py skips compile/fit
            for "bridge": true entries.
  verify    Bridge sanity: content == FA concat bytes, anchor-definition
            registry (build/tu/anchors.json) unique per chunk, alias TOs.
  tailsweep Split-policy sweep for the link tail word (exe 0x131a09):
            bridge content is chunk-boundary tiled, so splitting a unit at
            an internal chunk boundary contributes byte-identical halves;
            the tail word is a chaotic function of the obj decomposition.
  parity    Stage C: compile merged TU sources, adopt rows passing the
            masked per-row parity (re-based patches + pad splices), split
            the rest out verbatim. (Implemented in a later stage.)
  finalize  Stage D: tools/swap.json <- final set; chunked config aside.

Inputs (read-only): tools/swap.json, build/survey/tu_map.json,
build/layout.json, build/reloc_map.json, FA/FA.EXE.
Scratch: build/tu/ (gitignored). Staging config: tools/swap.tu.json.
"""
import bisect
import contextlib
import hashlib
import io
import json
import os
import re
import struct
import subprocess
import sys

sys.path.append(os.path.dirname(os.path.abspath(__file__)))
from anchors import Anchors
from peref import IMAGE_BASE
import coff
import fitobj
import mkstub
from padcensus import composition as pad_composition

SWAP = "tools/swap.json"
OUT = "tools/swap.tu.json"
PLAN = "build/tu/plan.json"
ANCHORS_JSON = "build/tu/anchors.json"
SRC_DIR = "src/tu"
FLAGS_MERGED = "/c /O2 /Gy /G5 /Ob0"


def fa_bytes():
    return open("FA/FA.EXE", "rb").read()


def load():
    L = json.load(open("build/layout.json"))
    tms = json.load(open("build/survey/tu_map.json"))
    es = json.load(open(SWAP))
    for e in es:
        if isinstance(e["rva"], str):
            e["rva"] = int(e["rva"], 0)
        if "span" in e:
            s = e["span"]
            e["span"] = (int(s, 0) if isinstance(s, str) else s) or None
        for k in ("map", "alias"):      # legacy dead keys
            e.pop(k, None)
    tcs = sorted(L["text_chunks"], key=lambda c: c["rva"])
    return L, tms, es, tcs


def anchor_name(c):
    return c["name"] or "$FA$_t_%06x" % c["va"]


def chunks_in(tcs, lo, hi):
    return [c for c in tcs if lo <= c["rva"] < hi]


# ---------------------------------------------------------------- units ----
def build_units(tms, es, tcs):
    """Units = consecutive TUs merged where (a) an entry's span crosses the
    TU boundary or (b) the TU has no entries of its own (a neighboring
    entry's span covers it — StartGameThread spans TUs 258-260). Unit
    extents tile .text: unit i = [lo(first TU), lo(next unit's first TU)),
    last extends to the last chunk end — inter-TU pad chunks fall LEFTward
    to the covering unit. Rows (entries) within a unit tile it 1:1."""
    lo = [t["lo_rva"] for t in tms]
    text_lo = tcs[0]["rva"]
    text_hi = tcs[-1]["rva"] + tcs[-1]["size"]
    assert lo[0] == text_lo, (hex(lo[0]), hex(text_lo))

    def tu_of(rva):
        return bisect.bisect_right(lo, rva) - 1

    edge = set()                      # TU i joins TU i+1 (span crosses lo[i+1])
    for e in es:
        s = e.get("span")
        if not s:
            continue
        t0, t1 = tu_of(e["rva"]), tu_of(e["rva"] + s - 1)
        for k in range(t0, t1):
            edge.add(k)
    has = [False] * len(tms)
    for e in es:
        has[tu_of(e["rva"])] = True
    units, cur = [], [0]
    for i in range(1, len(tms)):
        if cur and (i - 1) not in edge and has[i]:
            units.append(cur)
            cur = []
        cur.append(i)
    units.append(cur)
    assert all(any(has[j] for j in u) for u in units), "unit with no entries"

    starts = [lo[u[0]] for u in units]
    starts[0] = text_lo
    ends = starts[1:] + [text_hi]
    out = []
    for i, u in enumerate(units):
        rows = sorted((e for e in es if tu_of(e["rva"]) in u),
                      key=lambda e: e["rva"])
        for j, e in enumerate(rows):
            nxt = rows[j + 1]["rva"] if j + 1 < len(rows) else ends[i]
            e["_end"] = nxt
            if e.get("span"):
                assert e["rva"] + e["span"] == nxt, \
                    ("span row must extend to the next row/unit end",
                     hex(e["rva"]), hex(e["span"]), hex(nxt))
        out.append(dict(id=i, tu_ids=u, rva=starts[i], end=ends[i],
                        rows=rows))
    # units tile .text; rows tile each unit
    for i in range(len(out) - 1):
        assert out[i]["end"] == out[i + 1]["rva"], i
    assert out[0]["rva"] == text_lo and out[-1]["end"] == text_hi
    assert sum(len(u["rows"]) for u in out) == len(es), "rows not 1:1"
    return out


# -------------------------------------------------- src/tu file emission ----
LANDMARK_RE = re.compile(r"[^0-9A-Za-z]")
INCLUDE_RE = re.compile(r"#include\s+(.+)$")


def landmark_of(tms, u):
    """(landmark, first TU id) — the first named row in rva order."""
    for i in u["tu_ids"]:
        for r in tms[i]["rows"]:
            nm = r.get("name")
            if nm:
                base = nm.split("@@")[0].lstrip("_?") or "anon"
                return LANDMARK_RE.sub("_", base).strip("_") or "anon", i
    return "anon_%05x" % (u["rva"] + IMAGE_BASE), u["tu_ids"][0]


def plan_tags(units, tms):
    multi = [u for u in units if len(u["rows"]) > 1]
    seen = {}
    for u in multi:
        lm, ti = landmark_of(tms, u)
        tag = "%03d__%s" % (ti, lm)
        b = tag.lower()
        if b in seen:               # case-insensitive uniqueness (NT FS)
            k = 2
            while ("%s_%d" % (b, k)) in seen:
                k += 1
            tag = "%s_%d" % (tag, k)
            b = tag.lower()
        seen[b] = u["id"]
        u["landmark"], u["tag"], u["obj"] = lm, tag, "tu_" + tag
    return multi


def emit_src(u, tms):
    """Concatenate the unit's row sources (rva order), with row headers and
    exact-duplicate #include dedupe. No file for single-row units (verbatim
    entries), mixed-language units, or rows without src. Returns (path, ext,
    langs) or None (reason in u['no_src'])."""
    if len(u["rows"]) == 1:
        return None
    # Row compile language = the row's own source-file extension (what the
    # chunked pipeline compiled) — NOT tu_map's "lang" field, which
    # disagrees with the extension for 622 rows (616 .c-src "cpp", 6
    # .cpp-src "c") and would leave bare externs unmapped (LNK2001 class).
    langs = {"cpp" if e["src"].endswith(".cpp") else "c" for e in u["rows"]}
    if len(langs - {"c"}) > 1:
        u["no_src"] = "mixed language " + "/".join(sorted(langs))
        return None
    if not all(e.get("src") for e in u["rows"]):
        u["no_src"] = "row without src"
        return None
    ext = ".cpp" if "cpp" in langs else ".c"
    seen_inc = set()
    inc_lines = []
    parts = ["/* TU rva %#x..%#x, %d rows — generated by tools/regroup.py"
             " plan */" % (u["rva"], u["end"], len(u["rows"]))]
    for e in u["rows"]:
        body = open(e["src"]).read().splitlines()
        while body and body[0] == "":
            body.pop(0)
        while body and body[-1] == "":
            body.pop()
        wrap = ext == ".cpp" and not e["src"].endswith(".cpp")
        # .c rows inside a .cpp TU keep C linkage (their objs' map FROMs and
        # the definers they reference are C-spelled; bare externs would
        # become C++-decorated refs the maps don't carry — LNK2001 class)
        if wrap:
            parts += ["#ifdef __cplusplus", 'extern "C" {', "#endif"]
        for ln in body:
            m = INCLUDE_RE.match(ln.strip())
            if m:
                inc = m.group(1).strip()
                if inc in seen_inc:
                    continue
                seen_inc.add(inc)
                if wrap:
                    inc_lines.append(ln)   # standard headers: out of the
                    continue               # extern "C" block
                parts.append(ln)
                continue
            parts.append(ln)
        if wrap:
            parts += ["#ifdef __cplusplus", "}", "#endif"]
        parts.append("")
    if inc_lines:
        parts = [parts[0]] + inc_lines + parts[1:]
    fn = os.path.join(SRC_DIR, u["tag"] + ext)
    open(fn, "w").write("\n".join(parts) + "\n")
    return fn


# ----------------------------------------------------------------- plan ----
def cmd_plan(args):
    out = args[0] if args else OUT
    L, tms, es, tcs = load()
    units = build_units(tms, es, tcs)
    multi = plan_tags(units, tms)
    print("units: %d (%d multi-row); single-row units kept verbatim"
          % (len(units), len(multi)))
    os.makedirs(SRC_DIR, exist_ok=True)
    os.makedirs("build/tu", exist_ok=True)
    collisions = []
    for u in units:
        u["src_file"] = emit_src(u, tms)
        if u.get("no_src"):
            collisions.append(dict(obj=u.get("obj"), reason=u["no_src"],
                                   rows=[hex(e["rva"]) for e in u["rows"]]))

    out_entries = []
    for u in units:
        if len(u["rows"]) == 1:
            out_entries.append(u["rows"][0])
            continue
        maps, mconf = [], None
        fr = {}
        for e in u["rows"]:
            for m in e.get("maps", []):
                f = re.split(r"[+-]", m.split("=", 1)[0], maxsplit=1)[0]
                t = m.split("=", 1)[1] if "=" in m else ""
                if f in fr and fr[f] != t:
                    mconf = "%s: %s vs %s" % (f, fr[f], t)
                fr.setdefault(f, t)
                maps.append(m)
        cs = chunks_in(tcs, u["rva"], u["end"])
        aliases = ["%#x=%s" % (c["rva"] - u["rva"], anchor_name(c))
                   for c in cs if c["rva"] != u["rva"]]
        if not cs[0]["name"]:
            aliases.insert(0, "0=%s" % anchor_name(cs[0]))
        ent = dict(rva=u["rva"], obj=u["obj"],
                   src=u.get("src_file") or u["rows"][0].get("src"),
                   flags=FLAGS_MERGED, span=u["end"] - u["rva"],
                   bridge=True,
                   notes="regroup unit %s (rows: %s)" % (
                       u["tag"], ", ".join(hex(e["rva"]) for e in u["rows"])),
                   rows=[hex(e["rva"]) for e in u["rows"]])
        if maps:
            ent["maps"] = maps
        if aliases:
            ent["aliases"] = aliases
        if mconf:
            ent["_split_cause"] = "map conflict " + mconf
        out_entries.append(ent)
    assert all(out_entries[i]["rva"] < out_entries[i + 1]["rva"]
               for i in range(len(out_entries) - 1)), "not rva-ordered"
    json.dump(out_entries, open(out, "w"), indent=1)

    plan = [dict(id=u["id"], tu_ids=u["tu_ids"], rva=u["rva"], end=u["end"],
                 obj=u.get("obj"), tag=u.get("tag"), landmark=u.get("landmark"),
                 src_file=u.get("src_file"),
                 verdict=None,
                 rows=[dict(rva=e["rva"], end=e["_end"], obj=e["obj"],
                            src=e["src"], span=e.get("span")) for e in u["rows"]])
             for u in units]
    json.dump(plan, open(PLAN, "w"), indent=1)
    json.dump(collisions, open("build/tu/collisions.json", "w"), indent=1)
    print("wrote %s (%d entries), %s, %d flagged unit(s)"
          % (out, len(out_entries), PLAN, len(collisions)))


def load_plan_units(plan_path=PLAN):
    """Rebuild the unit dicts (with live entry directives) from plan.json."""
    L, tms, es, tcs = load()
    es_by_rva = {e["rva"]: e for e in es}
    plan = json.load(open(plan_path))
    units = []
    for p in plan:
        rows = []
        for r in p["rows"]:
            e = es_by_rva.pop(int(r["rva"], 0)) if isinstance(r["rva"], str) \
                else es_by_rva.pop(r["rva"])
            e["_end"] = int(r["end"], 0) if isinstance(r.get("end"), str) else r["end"]
            rows.append(e)
        units.append(dict(id=p["id"], tu_ids=p["tu_ids"], rva=int(p["rva"], 0)
                          if isinstance(p["rva"], str) else p["rva"],
                          end=int(p["end"], 0) if isinstance(p["end"], str)
                          else p["end"], rows=rows, obj=p["obj"]))
    assert not es_by_rva, "plan rows lost: %d" % len(es_by_rva)
    return L, tms, es, tcs, units


# --------------------------------------------------------------- bridge ----
def merge_spans(u, split, tcs):
    """Unit span(s) [(rva, end)]. A split policy (split size per unit id,
    build/tu/split.json) tiles multi-row units at internal chunk boundaries
    so each segment stays under the size — byte-identical contributions."""
    lo, end = u["rva"], u["end"]
    mx = (split or {}).get(str(u["id"]))
    if not mx:
        return [(lo, end)]
    cs = chunks_in(tcs, lo, end)
    segs, cur, size = [], lo, 0
    for c in cs[:-1]:
        size += c["size"]
        if size >= mx:
            segs.append((cur, c["rva"] + c["size"]))
            cur = c["rva"] + c["size"]
            size = 0
    segs.append((cur, end))
    return segs


def build_bridge_obj(u, lo, hi, tcs, L, A, rm, fpo_set, exe):
    cs = chunks_in(tcs, lo, hi)
    assert cs[0]["rva"] == lo and sum(c["size"] for c in cs) == hi - lo, \
        (hex(lo), hex(hi))
    content = bytearray()
    relocs = []
    for c in cs:
        seg = c["rva"] - lo
        raw = exe[c["off"]:c["off"] + c["size"]]
        content += raw
        for os_ in rm["text"].get(str(c["va"]), []):
            o = int(os_)
            v = struct.unpack_from("<I", raw, o)[0]
            an = A.anchor(v)
            if an is None:
                raise SystemExit("UNRESOLVED anchor %#x in chunk %#x"
                                 % (v, c["va"]))
            struct.pack_into("<I", content, seg + o, (v - an[1]) & 0xFFFFFFFF)
            relocs.append((seg + o, an[0], coff.RELOC_DIR32))
    name = anchor_name(cs[0])
    dbg_parts = []
    for c in cs:
        if (c["rva"], c["size"]) not in fpo_set:
            continue
        r = (bytes.fromhex(c["fpo_rec"]) if c.get("fpo_rec") else
             struct.pack("<IIIHBB2x", c["rva"], c["size"], 0, 0, 0, 0))
        dbg_parts.append((".debug$F", coff.S_DEBUGF_PLAIN,
                          b"\0\0\0\0" + r[4:],
                          [(0, anchor_name(c), coff.RELOC_DIR32NB)]))
    extra = [(anchor_name(c), c["rva"] - lo, 1, coff.SYM_EXTERNAL,
              coff.TYPE_FUNCTION, b"") for c in cs[1:]]
    return coff.build_stub_obj(bytes(content), 0x00100020, name,
                               fpo_rec=None, debugf_assoc=False,
                               more_sections=dbg_parts,
                               main_relocs=relocs, more_syms=extra)


def cmd_bridge(args):
    L, tms, es, tcs, units = load_plan_units()
    cfg = json.load(open(OUT))                 # staging config (parity-aware)
    brg = {e["obj"] for e in cfg if e.get("bridge")}
    split = (json.load(open("build/tu/split.json"))
             if os.path.exists("build/tu/split.json") else None)
    exe = fa_bytes()
    A = Anchors(L)
    rm = json.load(open("build/reloc_map.json"))
    fpo_set = set(mkstub.fa_fpo_records())
    built = skipped = 0
    for u in units:
        merges = bool(u["obj"]) and u["obj"] in brg
        if not merges:
            skipped += 1           # verbatim/natural entry: obj already built
            continue
        spans = merge_spans(u, split, tcs)
        for k, (lo, hi) in enumerate(spans):
            obj = build_bridge_obj(u, lo, hi, tcs, L, A, rm, fpo_set, exe)
            name = u["obj"] if len(spans) == 1 else "%s_s%d" % (u["obj"], k)
            open("build/pilot/%s_fit.obj" % name, "wb").write(obj)
            built += 1
    print("bridge: wrote %d fit obj(s), skipped %d single-row unit(s)"
          % (built, skipped))


# ------------------------------------------------------------- parity ----
VERDICTS = "build/tu/verdicts.json"
PROV_KEY_RE = re.compile(
    r"^(patch) ?((?:0x[0-9a-fA-F]+|\d+)(?:\s*/\s*(?:0x[0-9a-fA-F]+|\d+))*)"
    r"((?:,\s*(?:\d+|0x[0-9a-fA-F]+))*)"
    r"(?:\s*\(([^()]*)\))?"
    r"([,:])(.*)$", re.S)


def _apply_specs(buf, specs):
    """Run fitobj's patch application with output muted; returns the
    resulting reloc list (moved originals + newsites)."""
    rl = []
    with contextlib.redirect_stdout(io.StringIO()):
        fitobj.apply_patches({"content": buf, "relocs": rl}, list(specs))
    return rl


def _mask_windows(mask, offs):
    for o in offs:
        for k in range(o, o + 4):
            if k < len(mask):
                mask[k] = 1


def _run_report(mask, a, b):
    d = [i for i in range(min(len(a), len(b)))
         if i < len(mask) and not mask[i] and a[i] != b[i]]
    if not d:
        return []
    runs = []
    for i in d:
        if runs and i == runs[-1][1]:
            runs[-1][1] = i + 1
        else:
            runs.append([i, i + 1])
    return ["%#x-%#x" % (x, y - 1) for x, y in runs[:6]]


def _row_fixups(rm, tcs, r0, r1):
    """FA .reloc fixup offsets (row-relative 4-B windows) over [r0, r1)."""
    out = []
    for c in chunks_in(tcs, r0, r1):
        out += [c["rva"] - r0 + int(s) for s in rm["text"].get(str(c["va"]), [])]
    return out


def _row_fa(tcs, exe, r0, r1):
    return b"".join(exe[c["off"]:c["off"] + c["size"]]
                    for c in chunks_in(tcs, r0, r1))


def _sim_row(row, msec, rm, tcs, exe):
    """Apply the row's ORIGINAL (chunk-relative) directives to its merged-
    compile code and compare against FA row bytes. Returns (ok, why)."""
    cs = chunks_in(tcs, row["rva"], row["_end"])
    F = row["_end"] - row["rva"]
    fa = bytearray(_row_fa(tcs, exe, row["rva"], row["_end"]))
    buf = bytearray(msec["content"])
    rl = _apply_specs(buf, row.get("patch", []))
    if len(buf) > F:
        return False, "sim %#x B > FA row %#x B" % (len(buf), F), rl
    mask = bytearray(F)
    _mask_windows(mask, [o for o, _, _ in rl])
    _mask_windows(mask, _row_fixups(rm, tcs, row["rva"], row["_end"]))
    d = _run_report(mask, buf, fa + bytearray(F - len(fa)))
    if d:
        return False, "sim != FA at " + " ".join(d), rl
    return True, "", rl


def _rebase_spec(spec, base):
    parts = spec.split(",")
    parts[0] = "%#x" % (int(parts[0], 0) + base)
    return ",".join(parts)


def _shift_prov(p, shift, rowrva):
    """Re-base a provenance string's patch offsets; 'tail:' stays verbatim.
    Attribution prefix '(row 0x<rva>)' goes after the key colon. Comma
    suffixes (oldlen / ',site' newsite tokens) are patch-relative or
    lengths — they ride along unshifted. Paren-form keys keep their
    description verbatim: 'patch 0x125 (jle disp …): …' →
    'patch 0x135 (jle disp …): (row 0x5e9a5) …'."""
    m = PROV_KEY_RE.match(p)
    if not m:
        return p
    toks = [int(t.strip(), 0) + shift for t in m.group(2).split("/")]
    out = ("patch " + "/".join("%#x" % t for t in toks) +
           (m.group(3) or ""))
    if m.group(4):
        out += " (%s)" % m.group(4)
    return out + m.group(5) + " (row %#x) " % rowrva + m.group(6)


def _emit_natural(u, msec, b, r, psrc, rm, tcs, exe):
    """Emit the natural (prefix) entry adopting the first r rows of unit u.
    Returns (entry, kind) or (None, reason). The emission is validated by
    simulating fitobj's exact pass (patches + tail) over the merged (or
    truncated) content before the entry is returned."""
    rows = u["rows"]
    prefix = r < len(u["rows"])
    kind = "prefix" if prefix else "natural"
    lo, end = u["rva"], rows[r - 1]["_end"]
    cs = chunks_in(tcs, lo, end)
    assert cs[0]["rva"] == lo and sum(c["size"] for c in cs) == end - lo
    fa_u = b"".join(exe[c["off"]:c["off"] + c["size"]] for c in cs)
    # merged (or truncated) base content + its combined reloc list
    content = bytearray()
    rl0 = []
    for j in range(r):
        content += msec[j]["content"]
        rl0 += [(o + b[j], n_, t) for o, n_, t in msec[j]["relocs"]]
    specs, provs = [], []
    D = 0
    for j in range(r):
        row = rows[j]
        F = row["_end"] - row["rva"]
        base = b[j] + D
        if row.get("patch"):
            specs += [_rebase_spec(p, base) for p in row["patch"]]
            for pr in row.get("provenance", []):
                provs.append(_shift_prov(pr, base, row["rva"]))
        if j == r - 1:
            # the last adopted row owns the entry's tail directive: its
            # non-patch provenance (tail: / gate-repair: keys) carries
            # over verbatim even when the row itself has no patches
            provs += [pr for pr in row.get("provenance", [])
                      if not pr.startswith("patch")]
        # row-local sim: end position of the patched code (FA coords)
        buf = bytearray(msec[j]["content"])
        rl = _apply_specs(buf, row.get("patch", []))
        L_end = len(buf)                            # <= F (arbitration ok'd)
        if j < r - 1 and L_end < F:
            # intermediate row: FA pad beyond the patched code must ride in
            # the merged obj (last row covers it with its tail directive)
            pad = fa_u[(row["rva"] - lo) + L_end:(row["rva"] - lo) + F]
            specs.append("%#x,0,%s" % (b[j] + D + L_end, pad.hex()))
            tprov = [p2 for p2 in row.get("provenance", [])
                     if p2.startswith("tail:")]
            if tprov:
                for p2 in tprov:
                    provs.append("patch %#x: (row %#x) %s" % (
                        b[j] + D + L_end, row["rva"], p2[len("tail:"):]))
            else:
                comp = pad_composition(bytes(pad))
                desc = ("+".join(comp) if comp else "verbatim FA bytes")
                provs.append("patch %#x: (row %#x) toolchain-diff - FA "
                             "interior pad splice beyond CL code "
                             "(%d B %s, unkeyed in the row's fit)"
                             % (b[j] + D + L_end, row["rva"], len(pad), desc))
            D += F - len(msec[j]["content"])
        elif j < r - 1:
            D += F - len(msec[j]["content"])
        elif j == r - 1 and row.get("tail"):
            pass                       # tail directive copied verbatim below
    # validate: simulate the fitobj pass and compare vs FA concat
    buf = bytearray(content)
    rl = _apply_specs(buf, specs)
    # entry tail semantics = fitobj's: the FA concat residue beyond the
    # contributed code is appended verbatim (--tail-accept when the last
    # row caries a "tail" key, else it must be a census-proven filler
    # composition); the "tail" field itself is only a marker, not hex
    tail_txt = rows[r - 1].get("tail")
    resid = bytes(fa_u[len(buf):])
    buf += resid
    comp = pad_composition(resid) if resid else ()
    if resid and comp is None and not tail_txt:
        return None, ("tail residue %#x B %s beyond CL code is not a census "
                      "composition and the last row has no tail key"
                      % (len(resid), resid.hex()))
    span = end - lo
    if len(buf) != span:
        return None, "emission sim %#x B != span %#x B" % (len(buf), span)
    mask = bytearray(len(buf))
    _mask_windows(mask, [o for o, _, _ in rl])
    _mask_windows(mask, _row_fixups(rm, tcs, lo, end))
    d = _run_report(mask, buf, fa_u)
    if d:
        return None, "emission sim != FA at " + " ".join(d)
    # maps (union over adopted rows) + per-chunk anchors
    maps, seen = [], set()
    for e in rows[:r]:
        for m in e.get("maps", []):
            if m not in seen:
                seen.add(m)
                maps.append(m)
    aliases = ["%#x=%s" % (c["rva"] - lo, anchor_name(c))
               for c in cs if c["rva"] != lo]
    if not cs[0]["name"]:
        aliases.insert(0, "0=%s" % anchor_name(cs[0]))
    ent = dict(rva=lo, obj=u["obj"], src=psrc[u["obj"]], flags=FLAGS_MERGED,
               span=span, merge_text=True,
               notes="regroup %s adoption of rows %s (unit %d)" % (
                   kind, ", ".join(hex(x["rva"]) for x in rows[:r]), u["id"]),
               rows=[hex(x["rva"]) for x in rows[:r]])
    if prefix:
        ent["merge_keep"] = r
    if maps:
        ent["maps"] = maps
    if aliases:
        ent["aliases"] = aliases
    if specs:
        ent["patch"] = specs
    if tail_txt:
        ent["tail"] = tail_txt
    if provs:
        ent["provenance"] = provs
    return ent, dict(kind=kind, span=span)


def cmd_parity(args):
    L, tms, es_orig, tcs, units = load_plan_units()
    plan = json.load(open(PLAN))
    psrc = {p["obj"]: p.get("src_file") for p in plan}
    rm = json.load(open("build/reloc_map.json"))
    exe = fa_bytes()
    cur = {e["obj"]: e for e in json.load(open(OUT))}   # staging config
    # ---- pass 0: candidates + pre-compile skips
    cand, keep = [], {}
    for u in units:
        if len(u["rows"]) < 2:
            continue
        srcf = psrc.get(u["obj"])
        if not srcf or not os.path.exists(srcf):
            keep[u["id"]] = "no merged src"
            continue
        fr, conf = {}, False
        for e in u["rows"]:
            for m in e.get("maps", []):
                f = re.split(r"[+-]", m.split("=", 1)[0], maxsplit=1)[0]
                t = m.split("=", 1)[1] if "=" in m else ""
                if f in fr and fr[f] != t:
                    conf = True
                fr.setdefault(f, t)
        if conf:
            keep[u["id"]] = "map conflict"
            continue
        cand.append((u, srcf))
    # ---- pass 1: batch V1 compile of merged sources (todo = units whose
    # compiled obj is absent; PARITY_KEEP skips those whose obj already
    # exists, everything else compiles unconditionally — never assume a
    # verdict from a missing obj)
    os.makedirs("build/pilot", exist_ok=True)
    jobs = [(srcf, u["obj"]) for u, srcf in cand]
    oks = set()
    if os.environ.get("PARITY_KEEP"):           # resume: reuse compiled objs
        for _, objn in jobs:
            if os.path.exists("build/pilot/%s.obj" % objn):
                oks.add(objn)
    todo = [(srcf, objn) for srcf, objn in jobs if objn not in oks]
    for srcf, objn in todo:
        p = "build/pilot/%s.obj" % objn
        if os.path.exists(p):
            os.remove(p)                        # stale obj, force recompile
    out = ""
    if todo:
        per = 180
        from swap import DOCKER_PLAIN
        for i in range(0, len(todo), per):
            parts = []
            for src, objn in todo[i:i + per]:
                cl = ("wine Z:/opt/msvc420/bin/CL.EXE /nologo " + FLAGS_MERGED
                      + " Z:/work/%s /FoZ:/work/build/pilot/%s.obj"
                      % (src, objn))
                parts.append('( %s ) && echo __OK__%s || echo __FAIL__%s'
                             % (cl, objn, objn))
            r = subprocess.run(DOCKER_PLAIN % dict(
                uid=os.getuid(), gid=os.getgid(), cmd="; ".join(parts)),
                shell=True, capture_output=True, text=True)
            out += r.stdout + r.stderr
    oks = oks | {l[len("__OK__"):].strip() for l in out.splitlines()
           if l.startswith("__OK__")}
    # ---- pass 2: arbitration per row
    vfail = []
    for u, srcf in cand:
        if u["obj"] not in oks or not os.path.exists(
                "build/pilot/%s.obj" % u["obj"]):
            keep[u["id"]] = "compile failed"
            continue
        secs, defs = fitobj.read_obj("build/pilot/%s.obj" % u["obj"])
        msec = [s for s in secs if s["name"] == ".text"]
        if len(msec) != len(u["rows"]):
            keep[u["id"]] = ".text sections %d != rows %d" % (
                len(msec), len(u["rows"]))
            continue
        bad_rows = []
        # merged obj: map COFF secnum (1-based, over ALL sections) -> .text
        # index, so definer-row symbols resolve against the right row tile
        tmap, ti = {}, 0
        for _si, _s in enumerate(secs, 1):
            if _s["name"] == ".text":
                tmap[_si] = ti
                ti += 1
        for j, row in enumerate(u["rows"]):
            _ssecs, sdefs = fitobj.read_obj(
                "build/pilot/%s.obj" % row["obj"])
            _st = [s for s in _ssecs if s["name"] == ".text"]
            assert len(_st) == 1
            ssec = _st[0]
            ssecnum = next(_k for _k, _s in enumerate(_ssecs, 1)
                           if _s["name"] == ".text")
            why = None
            if len(ssec["content"]) != len(msec[j]["content"]):
                why = ("merged code %#x B != standalone %#x B"
                       % (len(msec[j]["content"]), len(ssec["content"])))
            else:
                mask = bytearray(len(ssec["content"]))
                _mask_windows(mask, [o for o, _, _ in ssec["relocs"]])
                _mask_windows(mask, [o for o, _, _ in msec[j]["relocs"]])
                d = _run_report(mask, msec[j]["content"], ssec["content"])
                if d:
                    why = "merged code diverges from standalone at " + \
                        " ".join(d)
            if not why:
                # reloc identity for CL-local $L labels: the merged row's
                # local-label fixups must land at the same RVAs as the
                # standalone obj's. Masked content compares cannot see CL
                # re-placing switch-case labels into another section of
                # the same TU (jump-table class, seen at the gate 3x).
                bad = []
                srel, mrel = ssec["relocs"], msec[j]["relocs"]
                if len(srel) != len(mrel):
                    bad.append("reloc count %d vs %d" % (len(srel), len(mrel)))
                else:
                    for (so, sn, st), (mo, mn, mt) in zip(srel, mrel):
                        sd, md = sdefs.get(sn), defs.get(mn)
                        if sd is not None and md is not None:
                            mrow = tmap.get(md[1])
                            if mrow is None or sd[1] != ssecnum or (
                                    row["rva"] + sd[0] !=
                                    u["rows"][mrow]["rva"] + md[0] or
                                    st != mt):
                                bad.append("%#x %s/%s rva" % (mo, sn, mn))
                        elif (sd is not None) != (md is not None) and \
                                (sn.startswith("$L") or
                                 (mn or "").startswith("$L")):
                            bad.append("%#x %s/%s local" % (mo, sn, mn))
                if bad:
                    why = "reloc targets differ from standalone: " + \
                        ", ".join(bad[:6])
            if not why:
                # patch-shape safety for merged (intermediate) rows only;
                # the last row keeps its own buffer-extension semantics.
                is_last = j == len(u["rows"]) - 1
                if not is_last:
                    C = len(msec[j]["content"])
                    for p in row.get("patch", []):
                        parts = p.split(",")
                        off, oldlen = int(parts[0], 0), int(parts[1], 0)
                        if (oldlen > 0 and off + oldlen > C) or off > C:
                            why = ("patch %s outside row code (C=%#x)"
                                   % (p, C))
                            break
            if why:
                bad_rows.append((j, why))
                vfail.append("%s row[%d] %#x: %s"
                             % (u["obj"], j, row["rva"], why))
            else:
                ok, why2, _ = _sim_row(row, msec[j], rm, tcs, exe)
                if not ok:
                    bad_rows.append((j, "sim " + why2))
                    vfail.append("%s row[%d] %#x: sim %s"
                                 % (u["obj"], j, row["rva"], why2))
        u["_bad"] = bad_rows
    # ---- pass 3: unit assembly + config emission
    out_entries = []
    stats = dict(natural=0, prefix=0, bridge=0, rows_nat=0, rows_verb=0)
    verdicts = []
    for u in units:
        rows = u["rows"]
        if len(rows) == 1:
            out_entries.append(rows[0])
            continue
        if u["id"] in keep:
            stats["bridge"] += 1
            verdicts.append(dict(id=u["id"], obj=u["obj"],
                                 kind="bridge", reason=keep[u["id"]],
                                 rows=[hex(r["rva"]) for r in rows]))
            out_entries.append(cur[u["obj"]])
            continue
        msec = [s for s in fitobj.read_obj(
            "build/pilot/%s.obj" % u["obj"])[0] if s["name"] == ".text"]
        b = []
        a = 0
        for m in msec:
            b.append(a)
            a += len(m["content"])
        r = min((j for j, _ in u["_bad"]),
                default=len(u["rows"]))
        if r == 0:
            stats["bridge"] += 1
            verdicts.append(dict(id=u["id"], obj=u["obj"], kind="bridge",
                                 reason="first row not adoptable",
                                 rows=[hex(x["rva"]) for x in rows]))
            out_entries.append(cur[u["obj"]])
            continue
        ent, info = _emit_natural(u, msec, b, r, psrc, rm, tcs, exe)
        if ent is None:
            keep[u["id"]] = info
            stats["bridge"] += 1
            verdicts.append(dict(id=u["id"], obj=u["obj"], kind="bridge",
                                 reason=info,
                                 rows=[hex(x["rva"]) for x in rows]))
            out_entries.append(cur[u["obj"]])
            continue
        out_entries.append(ent)
        verdicts.append(dict(id=u["id"], obj=u["obj"], kind=info["kind"],
                             adopt_rows=r,
                             rows=[hex(x["rva"]) for x in rows]))
        stats["rows_nat"] += r
        stats["natural" if info["kind"] == "natural" else "prefix"] += 1
        for row in u["rows"][r:]:
            out_entries.append(row)          # verbatim original entries
            verdicts[-1].setdefault("split_out", []).append(hex(row["rva"]))
            stats["rows_verb"] += 1
    assert all(out_entries[i]["rva"] < out_entries[i + 1]["rva"]
               for i in range(len(out_entries) - 1)), "not rva-ordered"
    json.dump(out_entries, open(OUT, "w"), indent=1)
    json.dump(verdicts, open(VERDICTS, "w"), indent=1)
    if vfail:
        json.dump(vfail, open("build/tu/parity_fails.json", "w"), indent=1)
    print("parity: %d natural, %d prefix(+verbatim), %d bridge; "
          "rows natural %d / verbatim %d; %d row failure(s)"
          % (stats["natural"], stats["prefix"], stats["bridge"],
             stats["rows_nat"], stats["rows_verb"], len(vfail)))
    if vfail:
        for x in vfail[:15]:
            print("  " + x)


# -------------------------------------------------------------- verify ----
def read_text(p):
    d = open(p, "rb").read()
    (mach, nsec, ts, symptr, nsym, opthsz, chars) = struct.unpack_from(
        "<HHIIIHH", d, 0)
    off = 20 + opthsz
    stro = symptr + nsym * 18
    syms = {}

    def sym_name(rec):
        if d[rec:rec + 4] == b"\0\0\0\0":
            o = stro + struct.unpack_from("<I", d, rec + 4)[0]
            return d[o:d.index(b"\0", o)].decode("latin-1")
        return d[rec:rec + 8].rstrip(b"\0").decode("latin-1")

    n = 0
    while n < nsym:
        rec = symptr + n * 18
        syms[n] = sym_name(rec)          # record-index -> name (reloc refs)
        n += 1 + d[rec + 17]
    for i in range(nsec):
        nm = d[off:off + 8].rstrip(b"\0").decode("latin-1")
        (vsz, va, rsz, rptr, relptr, lnptr, nrel, nln, fl) = \
            struct.unpack_from("<IIIIIIHHI", d, off + 8)
        if nm == ".text":
            relocs = [(o, syms.get(_symptr, "#?"), t)
                      for (o, _symptr, t) in
                      (struct.unpack_from("<IIH", d, relptr + k * 10)
                       for k in range(nrel))]
            return rsz, d[rptr:rptr + rsz], relocs
        off += 40
    raise SystemExit("no .text section in " + p)


def cmd_verify(args):
    """Every bridge fit obj's .text == FA concat bytes over its span; every
    chunk anchor (bridge + verbatim single-row mains) defined exactly once;
    interior alias TOs defined by the owning entry."""
    L, tms, es, tcs = load()
    cfg = json.load(open(args[0] if args else OUT))
    exe = fa_bytes()
    from peref import IMAGE_BASE
    byrva = {c["rva"]: c for c in tcs}
    registry, errs, nobj, nmasked = {}, [], 0, 0
    for e in cfg:
        isbridge = bool(e.get("bridge")) and len(e.get("rows", []) or []) >= 2
        if isbridge:
            p = "build/pilot/%s_fit.obj" % e["obj"]
            rsz, content, rels = read_text(p)
            cs = chunks_in(tcs, e["rva"], e["rva"] + e["span"])
            own = [anchor_name(c) for c in cs]
        else:
            if e.get("merge_text"):
                continue   # natural/prefix: fitted at link time (fitobj
                           # --merge-text from the CL obj); verified there
                           # by the emission sim + the gate
            c = byrva[e["rva"]]
            cs = chunks_in(tcs, c["rva"], c["rva"] +
                           (e.get("span") or c["size"]))
            own = [anchor_name(c2) for c2 in cs]
            p = "build/pilot/%s_fit.obj" % e["obj"]
            if not os.path.exists(p):
                rels = None       # not yet fitted (link's compile step fits)
            else:
                rsz, content, rels = read_text(p)
                if len(cs) == 1:  # single-chunk verbatim: today's verified
                    rels = None   # obj — byte-proven at its own fit time
        if rels is not None:
            nobj += 1
            want = b"".join(exe[c2["off"]:c2["off"] + c2["size"]]
                            for c2 in cs)
            # The link fixes up every reloc'd dword to a final VA; before
            # the link the content dword carries an ADDEND (final − anchorVA)
            # where FA's raw bytes carry the absolute value — both bridge
            # objs (stub mechanism) and CL objs with remaps differ from raw
            # FA bytes exactly there, by design. Masked compare = the
            # wave-2 byte-verify's exemption rule applied in reverse.
            mask = bytearray(len(want))
            own_va = {}
            for c2 in cs:
                own_va[anchor_name(c2)] = c2["rva"] + IMAGE_BASE
            diffs = []
            for o, nm, t in rels:
                if o + 4 > len(content):
                    errs.append("%s: reloc @%#x past content end"
                                % (e["obj"], o))
                    break
                for k in range(o, min(o + 4, len(want))):
                    mask[k] = 1
                va = own_va.get(nm)
                if va is not None:
                    got = struct.unpack_from("<I", content, o)[0]
                    wv = struct.unpack_from("<I", want, o)[0]
                    exp = (wv - va) & 0xFFFFFFFF
                    if got != exp:
                        errs.append("%s: addend @%#x (%s): got %08x, want "
                                    "(%08x-%#x)=%08x" %
                                    (e["obj"], o, nm, got, wv, va, exp))
            for i in range(len(want)):
                if mask[i]:
                    nmasked += 1
                elif i >= len(content) or content[i] != want[i]:
                    diffs.append(i)
            if len(content) != len(want):
                errs.append("%s: .text size != FA concat (%d vs %d B)"
                            % (e["obj"], len(content), len(want)))
            elif diffs:
                runs = []
                for i in diffs:
                    if runs and i == runs[-1][1]:
                        runs[-1][1] = i + 1
                    else:
                        runs.append([i, i + 1])
                errs.append("%s: .text != FA concat at %d B (%s...)" %
                            (e["obj"], len(diffs), " ".join(
                                "%#x" % a for a in diffs[:4])))
        for nm in own:
            if nm in registry and registry[nm] != e["obj"]:
                errs.append("anchor %s defined twice (%s, %s)"
                            % (nm, registry[nm], e["obj"]))
            registry[nm] = e["obj"]
        for a in e.get("aliases", []):
            tofs, nm = a.split("=", 1)
            if int(tofs, 0) > 0:
                if nm not in registry:
                    errs.append("%s: interior alias TO %s not defined"
                                % (e["obj"], nm))
                elif registry[nm] != e["obj"]:
                    errs.append("%s: interior alias TO %s defined by %s"
                                % (e["obj"], nm, registry[nm]))
    json.dump(registry, open(ANCHORS_JSON, "w"), indent=1)
    if errs:
        for x in errs[:30]:
            print("  FAIL", x)
        raise SystemExit("verify: %d problem(s)" % len(errs))
    nb = len([e for e in cfg if e.get("bridge")])
    print("verify: ok — %d bridge/span objs checked vs FA concat "
          "(%d fixup-dword B masked) + %d verbatim, %d anchors registered"
          % (nobj, nmasked, len(cfg) - nb, len(registry)))


def sha(path):
    return hashlib.sha256(open(path, "rb").read()).hexdigest()


def main():
    argv = sys.argv[1:]
    if not argv:
        print(__doc__)
        return
    name, args = argv[0], argv[1:]
    fn = globals().get("cmd_" + name)
    if fn is None:
        raise SystemExit("unknown subcommand: %s" % name)
    fn(args)


if __name__ == "__main__":
    main()