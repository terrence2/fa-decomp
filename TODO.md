# FA.EXE Decompilation Toolchain — TODO & Handoff Notes

Goal: incrementally reverse-engineer `FA/FA.EXE` (Jane's Fighters Anthology, retail 1.00F,
1997-08-11) source-free by swapping original-bytes stub objects for real decompiled C/C++,
keeping the linked output **byte-for-byte identical to FA.EXE at every step**.
Full context: `MSVC_VERSION.md` (toolchain evidence), approved plan at
`~/.claude/plans/can-you-figure-out-prancy-volcano.md`.

---

## DONE

### Phase 0 — Docker toolchain (working, proof passes)
- `docker/Dockerfile` — debian:trixie-slim + i386 wine + wine32 + libfaketime (BOTH arches)
  + xvfb + python3; `COPY vendor/MSVC420 → /opt/msvc420` (portable VC++ 4.2:
  CL.EXE/LINK.EXE/LIB.EXE/RC.EXE + include/ + lib/ incl. LIBCMT.LIB).
  Image name: `fa-decomp-env` (`make image`).
- `docker/entrypoint.sh` — wine prefix init via xvfb-run wineboot, `FA_EPOCH` default.
- `docker/proof.sh` — compiles+links hello.c twice, **DETERMINISM=PASS**: two links are
  byte-identical when the clock is frozen; real PE gets MakerLinkerVersion=4.20.
- `Makefile` — `image`, `proof` targets.

**Critical Docker/Wine gotchas (don't rediscover these):**
- Always `docker run --rm --user "$(id -u):$(id -g)" -e HOME=/tmp` — wine refuses prefixes
  in dirs it doesn't own.
- faketime: Debian has no `faketime` CLI; use `LD_PRELOAD` of BOTH
  `/usr/lib/x86_64-linux-gnu/faketime/libfaketime.so.1` AND
  `/usr/lib/i386-linux-gnu/faketime/libfaketime.so.1` (wine loader is i386) + `-e TZ=UTC
  -e FAKETIME="@1997-08-11 23:13:32"`. This pins the linker TimeDateStamp exactly to
  `0x33ef9c9c` — verified working.
- Wine paths: `Z:\opt\msvc420\bin\CL.EXE`, source as `Z:/work/...`.

### Phase 1 — Layout extraction (parser done, layout.json NOT yet emitted)
- `tools/parsesms.py` — WORKING `FA.SMS` parser. Format (decoded):
  `[u32 count][u32 zero][{u32 VA, u32 end_off} × (count-1)][u32 final VA][name pool]`,
  end_off = cumulative offset just past each symbol's NUL. `parse_sms(path)` → `[(VA, name)]`.
  3753 symbols: 2420 in .text, 7 in .rdata, 1099 in .data (includes CRT symbols).
- `tools/peref.py` — PE32 parser: sections, debug dir (lives INSIDE .rdata; read data-dir
  entry 6 at `opt+96+6*8`), exports, imports, **FPO**.
- FPO payload format (empirically verified): 16-byte header + 16-byte records
  (`<IIIH` + 2 pad = FPO_DATA: offStart, cbProcSize, cdwLocals, cbParams, 2 trailer bytes);
  ~2985 records. `parse_fpo()` now returns `(dict rva→rec, header16)` — **main() still uses
  the OLD signature and will crash until fixed** (see TODO 1).
- `tools/checkpe.py` — PE summary + `--expect-sha256` gate.
- `build/test/fpotest.obj` — ground-truth VC4.2 obj from cl `/MT /GX /O2 /Gy`, showing
  per-function COMDAT `.text` (flags 0x60501020, align 16) + paired `.debug$F`
  (flags 0x42101048, one 16-byte FPO_DATA + DIR32NB reloc to the function symbol).
  `.drectve`: `-defaultlib:LIBCMT -defaultlib:OLDNAMES`.

**Key FA.EXE facts** (full details in `MSVC_VERSION.md`): ImageBase 0x400000, sections
.text(VA 0x1000) .rdata(VA 0xe5000) .data(VA 0xe7000) .idata(0x18a000) .rsrc(0x18c000)
.reloc(0x18e000); debug payloads (MISC/FPO/NB10) appended after .reloc at file offsets
0x131a00 / 0x131b10 / 0x13d5b0; NB10 PDB path `E:\atf95\Release\FA.pdb`; module exports
"FA.exe" with 2 functions; imports WINMM/KERNEL32/USER32/DDRAW/wail32/CDRVDL32/CDRVHF32/
ADVAPI32.

**Milestone 0 design decision already made**: stub EVERYTHING — game code AND the static CRT
(the CRT stays original bytes forever, so libcmt is never linked; stubs carry the original
bytes with baked-in relative offsets, valid because placement must reproduce original VAs).

### Import synthesis probed (link 4.20) — decision: NO import libraries, direct `.idata$` objs
Probes live in `tools/probes/` (mkref.py, mkidr.py, idcheck.py, microtest.py; artifacts in
build/m0/ — gitignored). Facts, all verified against real `LINK.EXE` 4.20 runs:

- Real-section relocs (DIR32 or DIR32NB to `__imp__X@n`) synthesize COMPLETE `.idata`
  (descriptors + INT + IAT + hint/name + .reloc); relocs inside LNK_INFO/`.debug$F` sections
  produce descriptor-only entries (empty INT/IAT). `-include:` drectve is accepted but
  incomplete; command-line `/INCLUDE:"__imp__X@n"` works and is complete.
- **INT/IAT entry order is hash-driven given the import NAME set** (verified: 109-name
  KERNEL32 probe reproduced FA's exact order + hints), but multi-DLL sets interleave in ways
  we don't fully model — SDK libs alone would scramble FA's order.
- FA's exact 209-entry import set incl. hints: `build/fa_imports.json`
  (wail32 by-name w/ exact hints, CDRVDL32/CDRVHF32 by-ordinal, rest standard).
- **RESOLVED — direct `.idata$` group objects**: cut FA's `.idata` bytes at the
  linker-semantic boundaries and hand them to the linker as plain objects:
  `$2`=+0x000..0x0a0 (8 descriptors), `$3`=+0x0a0..0x0b4 (null import descriptor),
  `$4`=+0x0b4..0x42c (INT), `$5`=+0x42c..0x790 (IAT), `$6`=+0x790..0x14dc (hint/name strings).
  Link 4.20 concatenates in `$2→$6` order, passes content through **byte-for-byte unchanged**
  (even unmodified baked-in RVAs), emits section flags 0xc0000040 = FA's, and computes the
  data dirs from the group extents: DD1(imports) = `$2+$3` = 0xb4 ✓, DD12(IAT) = `$5` at
  +0x42c size 0x364 ✓. Byte-identical `.idata` (incl. the 0x124 pad to rawsz 0x1600);
  idirect2.exe artifacts confirm. Splitting `$2` at 0xa0 is load-bearing: putting the
  terminator inside `$2` inflates DD1 by 0x14 (linker adds `$2+$3`).
- Consequence: **skip crafting import libs entirely** (LIB /DEF can't make by-name entries
  with nonzero hints anyway); no `/INCLUDE` directives; stub .text carries no symbol refs.

### .reloc requirement (discovered — blocks stub-only link)
FA `.reloc` = 39,518 fixups (.text 36,340, .rdata 170, .data 3,008, .idata 0). The IAT gets
no base fixups (importer overwrites). Stub objs must carry REAL DIR32 relocations at FA's
fixup offsets (targets = containing chunk symbols; linker patches value = chunk VA → identity
with baked bytes) so the linker regenerates `.reloc` byte-identically.

### Note on `FA/FA_*.LIB` (resolved — do not chase this)
The shipped `FA_.LIB`, `FA_1.LIB` … `FA_23.LIB` files (and `WAIL32.DLL`, `CDRV*.DLL`,
`COMMSC32.DLL`, `IP.EXE`) in `FA/` are **game asset files, not build inputs** — they are
NOT import libraries for the game DLLs, and nothing at link time consumes them. They are
runtime-mission/campaign data the game loads itself. Do not spend any Milestone-0 effort
on them; the stub-only link needs only the 2 export directives in FA.EXE itself.

---

## TODO (in order)

### 1. Fix `tools/peref.py main()` → emit `build/layout.json`
- Update to the new `parse_fpo()` tuple signature (`fpo_recs, fpo_header = parse_fpo(pe)`).
- Build the chunked layout the stub generator needs:
  - `.text`: one chunk per FPO record (rva, size); assign SMS names by rva; split the
    residual ~15% gap at SMS symbol starts so gap blobs don't swallow named code.
  - `.data`: chunks from the 1099 SMS data symbols (extent = to next symbol VA).
  - Emit per-chunk: `{name|None, va, rva, size, fpo_present, bytes_file_offset}` plus
    section metadata, exports/imports, debug payload offsets.
- Sanity gate: chunks must tile .text exactly (sum of sizes + no overlap), same for .data.

### 2. Finish obj-format ground truth → `tools/coff.py`
- Re-dump `build/test/fpotest.obj` symbol table with a **correct 18-byte-record walker**
  (honor aux counts; read string table only for zeroed name slots). Last attempt walked off
  the end at sym[13] (aux mishandling) — the obj is fine, the walker was wrong.
- Capture exact aux-record contents for section symbols (SectionLength, CheckSum,
  Selection byte for COMDAT assoc./duplicate semantics).
- Write `tools/coff.py`: COFF I386 obj writer mirroring cl's output byte layout —
  `.text` COMDAT section + `.debug$F` (16-byte FPO_DATA + DIR32NB reloc) per stub, symbol
  table + string table + relocations, `.drectve` when needed.

### 3. `tools/mkstub.py` — one obj per chunk
- Input layout.json; emit stub objs: original bytes as section content, symbol name
  (demangle→keep raw SMS name), alignment, lifted FPO record.
- CRT/data stubs same mechanism (selection=any COMDAT or plain sections as analysis dictates).

### 4. Milestone 0 — stub-only full link (the big gate)
- Imports: direct `.idata$` group objs per the resolved probe above (5 objs, FA bytes).
- link 4.20 `/MACHINE:IX86 /SUBSYSTEM:WINDOWS`, entry `_WinMainCRTStartup` (stub obj exists:
  build/m0/stub_entry.obj), objs in layout order, export directives for the 2 FA.exe exports,
  resource `.res` (reconstruct 0x1200 bytes of .rsrc via RC), faketime-frozen clock, Wine
  drive `E:` at `atf95\Release` so NB10 PDB + MISC strings match.
- **Extend mkstub first**: add DIR32 relocs at FA's fixup offsets within each .text/.data
  chunk (see ".reloc requirement" above); .rdata's 170 fixups + debug dir handled separately.
- .rsrc raw stub (0x1200 bytes as a `.rsrc` section obj), .rdata stubbing (0x1452: debug dir
  + 170 fixups), debug payloads (MISC "Release/FA.exe", NB10 "E:\atf95\Release\FA.pdb" —
  Wine E: drive at `atf95\Release`), FPO payload order, frozen timestamp 0x33ef9c9c,
  section first-appearance order (.text .rdata .data .idata .rsrc .reloc).
- Iterate until `sha256(build/FA.exe) == sha256(FA/FA.EXE)`.

### 5. Phase 3 — workflow tooling
- `tools/gate.py` (gate 1, byte gate w/ symbol-window localization on failure).
- `tools/compare.py` (gate 2, per-function slice diff, reccmp-style).
- Build driver: link line = decompiled objs + stub objs, both in original address order;
  decompiled TUs must be address-contiguous runs.

### 6. Phase 4 — pilot decompilations
- 1 small C function, then 1 C++ member with throw site. Gate 2 iterates locally, gate 1
  must pass on commit.
- Flag discovery: `/MT /GX /O2`-family (`/Og /Oi /Ot /Ob1 /Oy`), `/G3` vs `/G5`, `/Zp8`.

### 7. Phase 5 — hardening
- Progress tracker JSON (N/3829 functions), CI gate, update `MSVC_VERSION.md` with the
  empirically resolved 4.2 vs 4.2b revision.

---

## Verification invariants (every handoff step)
1. Two identical builds (frozen clock) before trusting any diff.
2. Gate 1: `sha256(build/FA.exe) == sha256(FA/FA.EXE)` on every commit.
3. No third-party static code assumed in the EXE beyond CRT (audio/CD/net live in DLLs).