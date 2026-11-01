# ARCHITECTURE.md

## 1. Goal

Reconstruct the C/C++ source of `FA/FA.EXE` (Jane's Fighters Anthology,
retail 1.00F, 1997-08-11 — sha256 `c7d2c1cc…` (see `tools/gate.py`)) with **no original
sources**, by replacing functions with decompiled code in a rebuild that must
remain **byte-for-byte identical to the retail EXE at every commit**:

```
GATE 1: sha256(atf95/Release/FA.exe) == sha256(FA/FA.EXE)
```

Byte-identity is the arbiter of correctness for every claim — codegen matches,
ordering guesses, and global layouts are all proved, not assumed. A second,
softer metric, **Gate 2** (`tools/compare.py`), reports per-function byte-match
percentages and tracks decompilation progress as N/3829 functions.

## 2. How the build accomplishes it

The rebuild uses the **original toolchain**: Microsoft Visual C++ 4.2
(`CL.EXE` / `LINK.EXE` 4.20) running under Wine inside the `fa-decomp-env`
docker image, with `libfaketime` freezing the link's clock to the retail
timestamps (`@1997-08-11 23:12:40` = pdb-seed link, `23:13:32` = real link;
`FAKETIME_DISABLE_SHM=1` is mandatory — see memory note `fa-docker-faketime-hang`).

The image is constructed in layers, every layer byte-checked against the
original (each layer's rationale lives in `TODO.md` and the `tools/` docstrings):

1. **Layout** — `peref.py` walks the PE headers, `FA/FA.SMS` (the game's own
   symbol table, 3753 symbols) and the FPO records to derive
   `build/layout.json`: every byte of `.text`/`.data` partitioned into
   *chunks* (named symbols or unnamed gaps).
2. **Stubs** — `mkstub.py` emits COFF group-objects whose sections contain the
   *original* bytes, named exactly like FA's symbols (via `coff.py`).
   Hand-crafted objects cover `.idata` (`mkimp.py`), the `.rdata` literal
   region (`mkrdata.py`) and `.rsrc` (`mkrsrc.py` → CVTRES).
3. **Link** — `mkrsp.py` renders the link-4.20 response file in FA's exact
   object order; the resulting `FA.exe` is already byte-identical
   ("milestone 0"), modulo two known-linker deltas repaired by `fixreloc.py`
   (`.reloc` VirtualSize) and the pdb-seed link cycle.
4. **Swaps** — a decompiled function is compiled with CL 4.2 (`/c /O2 /Gy
   /G5`), its object is *fitted* into FA's chunk shape (`fitobj.py`), and the
   link line's stub for that chunk is replaced by the fitted object
   (`mkstub.py SPLIT_AT` regenerates a singleton stub; `mkrsp.py --replace`
   swaps it in). Fixed FA codegen quirks that pure C cannot express are
   repaired by explicit, documented `--patch` directives. The link cycle runs
   and Gate 1 re-verifies. If it passes, real source has provably replaced
   original code.

## 3. Tools

```
                       ┌────────────── analysis (read-only) ──────────────┐
                       │   parsesms.py ─┐                                 │
FA/FA.EXE ──> peref.py ┴───────────────► build/layout.json                 │
              └────────► build/reloc_tgts.json / reloc_map.json            │
                       │   (anchors.py resolves every fixup to a symbol)  │
                       └──────────────────────────────────────────────────┘
                                    │
      stub builders                 v            swap loop (per function)
┌─────────────────────────┐   ┌───────────────┐   src/Fn.c
│ mkstub.py (SPLIT_AT)    │   │   swap.py     │     │ CL 4.2 /c /O2 /Gy /G5
│ mkimp.py   (.idata)     │   │  (driver)     │     v
│ mkrdata.py (.rdata)     │   │ compile──► build/pilot/Fn.obj
│ mkrsrc.py  (.rsrc)      │   │    fitobj ═► build/pilot/Fn_fit.obj
└───────────┬─────────────┘   │ link ────► LINK 4.20 @faketime (──► FA.pdb)
            v                 │ gate ────► fixreloc.py ──► gate.py ──► GATE 1
       build/stubs_d/*.obj
            │                 (swap.py reads tools/swap.json and runs the
            v                  compile/fitobj/link/gate steps per entry;
       mkrsp.py ──► build/m0/m0linkD.rsp    the common bits are coff.py,
            │                               anchors.py, fitobj.py)
            v
       LINK.EXE 4.20 ──► atf95/Release/FA.exe ──► fixreloc.py ──► gate.py
```

| tool | role |
| --- | --- |
| `peref.py` | PE analysis → `build/layout.json` (chunks, symbols, FPO, imports/exports). |
| `parsesms.py` | Parses the game's `FA.SMS` symbol table (VA + name pool). |
| `coff.py` | COFF I386 object reader/writer mirroring VC4.2 output; used by `fitobj.py` and `mkstub.py`. |
| `mkstub.py` | Emits the byte-accurate stub group-objects for every `.text`/`.data` chunk; `SPLIT_AT=v1,v2,…` cuts singleton stubs for chunks being swapped. |
| `mkimp.py` / `mkrdata.py` / `mkrsrc.py` | Hand-crafted `.idata$`, `.rdata` and `.rsrc` contributions reproducing FA's PE structure exactly. |
| `anchors.py` | Resolves reloc targets to stub symbols (chunk symbol / `$FA$_t_…` gap anchor / `$FA$rdata0` / IAT slots). |
| `mkrsp.py` | Renders the link response file, preserving FA's object order; `--replace VA=obj` swaps in fitted decompiled objects. |
| `fitobj.py` | Adapts a CL object to FA's chunk: adds the FA tail pad + splices FA's FPO record, remaps relocations (`--map FROM=TO[+addend]`), repairs scheduler-level codegen deltas (`--patch`), optionally accepts FA residue tails (`--tail-accept`). |
| `swap.py` + `swap.json` | The driver: runs everything below for all entries in the version-controlled swap set. Steps run individually: `python3 tools/swap.py [compile\|link\|gate]`. |
| `mkrsp.py` | Renders `build/m0/m0linkD.rsp` preserving FA's exact object order; `--replace VA=obj` swaps a fitted decompiled object in. |
| `fixreloc.py` | Forces the `.reloc` VirtualSize to FA's 0x143d8 (wine-linker bookkeeping delta, proven inert). |
| `gate.py` | Gate 1: sha256 identity, with symbol-localized diffs on failure. |
| `compare.py` | Gate 2: per-function byte-match % — the progress metric and next-target picker. |
| `checkpe.py`, `sweeptail.py`, `tools/probes/` | One-shot validation and synthetic probing utilities used during the milestone-0 investigation (kept for reference). |

## 4. Workflow toward full decompilation

State of play: milestone 0 (stub-only rebuild) passed Gate 1; six functions
are swapped so far (`tools/swap.json`), each with its codegen findings recorded
in `TODO.md` Phase 4. The path from here is a function-at-a-time loop, always
shipped with a passing Gate 1:

1. **Pick** the next target: un-swapped chunk, ideally small/leaf-ish with few
   fixups (Gate 2's JSON ranks them).
2. **Understand** it: disassemble the chunk, map its relocation sites, note
   calling conventions, FPO record, and which globals it touches.
3. **Reconstruct** `src/<Name>.c` and iterate *offline* (compile + `fitobj`
   byte-compare only — no link) until it matches FA's chunk bytes.
4. **Register** it in `tools/swap.json` (maps/patch/tail when needed).
5. **Swap + gate**: `python3 tools/swap.py` → GATE 1 PASS.
6. **Commit** the source + entry, extending `TODO.md` with any new codegen
   tells. Pilot knowledge compounds: most functions reuse patterns already
   solved (fastcall, 16-bit params, switch tables, inlined memcpy, …).

Expected composition of the remaining 3,823 functions: large clusters share
idioms (CRT, fastcall arithmetic helpers, dialog/UI), so the per-function
effort drops as the pilot set grows. Scaling beyond a few dozen entries needs
batching of the stub-regen/link steps (Phase 5 in `TODO.md`), but the
mechanism is already proven end-to-end.

### Worked example: decompiling your first function

Environment assumed: repo root `fa-decomp`, docker image `fa-decomp-env` present.

```sh
cd /home/terrence/Projects/fa-decomp          # repo root

# 1) Prove the baseline on a fresh tree (stub-only, milestone 0):
python3 tools/swap.py link gate               # → GATE 1 PASS

# 2) Pick a target: smallest named chunks not yet in tools/swap.json
python3 tools/compare.py --json build/compare.json   # per-chunk match %
python3 - <<'EOF'
import json
raw = "".join(l for l in open("tools/swap.json")
              if not l.lstrip().startswith("//"))
done = {int(e["rva"], 0) for e in json.loads(raw)}
L = json.load(open("build/layout.json"))
cands = sorted((c for c in L["text_chunks"]
                if c["rva"] not in done and c["name"]),
               key=lambda c: c["size"])[:10]
for c in cands:
    print("%#x  %5d  %s" % (c["rva"], c["size"], c["name"]))
EOF

# 3) Disassemble the chosen chunk (rva 0x78b50 shown for LibRead):
python3 - <<'EOF'
import json
L = json.load(open("build/layout.json"))
c = next(c for c in L["text_chunks"] if c["rva"] == 0x78b50)
fa = open("FA/FA.EXE", "rb").read()
open("/tmp/blk.bin", "wb").write(fa[c["off"]:c["off"] + c["size"]])
print("disasm target: name=%s fpo=%s" % (c["name"], c["fpo_rec"]))
EOF
objdump -D -b binary -m i386 -Mintel --adjust-vma=0x478b50 /tmp/blk.bin

# 4) Reconstruct src/<Name>.c, then compile + fit offline and iterate:
docker run --rm --user $(id -u):$(id -g) -e HOME=/tmp -e TZ=UTC \
  -e FAKETIME_DISABLE_SHM=1 -v "$PWD":/work -w /work fa-decomp-env \
  bash -c "wine Z:/opt/msvc420/bin/CL.EXE /nologo /c /O2 /Gy /G5 \
           Z:/work/src/<Name>.c /FoZ:/work/build/pilot/<Name>.obj"
python3 tools/fitobj.py build/pilot/<Name>.obj 0x<rva> \
        --map '_myGlob=?realSym@@3PAUS@@A+0x4' [--patch ...]
# fitobj exits nonzero the moment code bytes/size disagree — fix and repeat.

# 5) Register the entry in tools/swap.json, then run the whole loop:
python3 tools/swap.py                          # → GATE 1 PASS

# 6) Commit source + swap.json entry (+ TODO.md tells):
git add src/<Name>.c tools/swap.json TODO.md
git commit -m "Phase 4 pilot N: <Name> ..."
```

Rules of the road: never link without a passing gate; never grow `swap.json`
beyond what Gate 1 proves; record every byte-matching lesson in `TODO.md` —
the fast route through 3,823 functions is not knowing more compiler theory,
but reusing the accumulated empirical codegen tells.