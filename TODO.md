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
- **faketime × wine deadlock (2026-10-31)**: LD_PRELOAD of both faketime libs +
  FAKETIME env hangs wine (process sleeps on futex, 0 CPU, no wineserver ever
  spawns). MUST also pass `-e FAKETIME_DISABLE_SHM=1` — the /dev/shm
  faketime_shm_*/faketime_sem_* handshake deadlocks wine's process tree.
  `FAKETIME_DONT_FAKE_MONOTONIC=1` does NOT help. With DISABLE_SHM the frozen
  clock still works (`date`, stat mtimes all 1997). Don't parse link output
  through `head` (SIGPIPE kills wine) — always `> log 2>&1`.

### Phase 1 — Layout extraction (parser done, layout.json NOT yet emitted)
- `tools/parsesms.py` — WORKING `FA.SMS` parser. Format (decoded):
  `[u32 count][u32 zero][{u32 VA, u32 end_off} × (count-1)][u32 final VA][name pool]`,
  end_off = cumulative offset just past each symbol's NUL. `parse_sms(path)` → `[(VA, name)]`.
  3753 symbols: 2420 in .text, 7 in .rdata, 1099 in .data (includes CRT symbols).
- `tools/peref.py` — PE32 parser: sections, debug dir (lives INSIDE .rdata; read data-dir
  entry 6 at `opt+96+6*8`), exports, imports, **FPO**.
- FPO payload format (empirically verified): 16-byte records
  (`<IIIH` + 2 pad = FPO_DATA: offStart, cbProcSize, cdwLocals, cbParams, 2 trailer bytes);
  2986 plain records, NO payload header (the 16-byte header I once thought I saw is the
  first record). `parse_fpo()` returns `(dict rva→rec, header16=b"")` — **main() still uses
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

### Special-section authoring limits (link 4.20)
- `.rsrc`-NAMED sections in objects are REJECTED outright — "Internal error during ZeroPad"
  (content/flag-invariant; tested 4-byte, full 0x1200, align variations). **RESOLVED (below):
  the link 4.20 resource pipeline is RC → .RES → CVTRES → obj with `.rsrc$01` (dir tree) +
  `.rsrc$02` (raw leaf blobs) sections — those contributions ARE accepted by LINK.**
- `.reloc` sections in objects are REJECTED — "Internal error during Pass1". The linker
  REBUILDS .reloc from obj fixup relocs; stubs must therefore carry real fixups (below).
- Plain/literal sections fine: `.rdata` literal obj accepted (prd1.exe probe).
- `/EXPORT:<name>` takes UNDECORATED names — `/EXPORT:expA` works, `/EXPORT:_expA` gives
  LNK2001+LNK1141 (matches FA's undecorated "T_HorizonProc"/"WRFogLayerUpdate").
- Synthesized export-dir placement: AFTER all obj `.rdata` contributions, 4-byte-aligned
  (FA: export dir at .rdata end 0x13f0..0x1452, stub contributions before it ✓ consistent).
- Synthesized export dir for `rde_ok.exe`: size 0x42 (2-name dir would be 0x62 with FA's
  names); FA module name "FA.exe" = /OUT basname ✓ convention.
- /EXPORT also builds an `<out>.lib` + `<out>.exp` import artifact — harmless, but on a
  subsequent FAILED link the failing run DELETES the stale `<out>` exe of a prior run
  (use distinct /OUT per probe).

### .rsrc round RESOLVED (2026-10-31) — byte-identical
- Feeding a `.res` **directly to LINK 4.20 fails under wine**: "LNK1104: cannot open file
  'TEMPFILE'" in Pass1 → link's internal CVTRES spawn never happens (traced: no
  CreateProcess, no temp file with WINEDEBUG=+file/+process; not faketime/TMP/PATH related).
  Workaround: run `CVTRES.EXE /machine:IX86 /readonly /nologo FA.res` OURSELVES → FA.obj
  (sections `.rsrc$01` [dir+entry tree] + `.rsrc$02` [leaf blobs]) and pass the obj to LINK —
  works, and the resulting image .rsrc is byte-identical.
- **.RES format (validated against RC.EXE 4.2 output `build/m0/rd/t.res`)**: null root block
  = 32 bytes `<IIIIIHHII> (0, 32, 0xFFFF, 0xFFFF, 0, 0, 0, 0, 0)`; leaf block same 32-byte
  header with dataSize=len(blob), integer type/name IDs = `0xFFFF | (id << 16)` (ordinal in
  HIGH word — the 0x8000|id form is .rsrc-DIRECTORY-only), dataVersion 0, memFlags (linker
  never copies it into .rsrc — any value ok), langID 0x409, version 0, characteristics 0,
  then blob padded to 4. `tools/mkrsrc.py` builds FA.res from FA's 5 leaf blobs
  (ICON 3/1 0x2e8 @.rsrc 0x160, ICON 3/2 0x8a8 @0x448, GROUP_ICON 14/103 0x22 @0xcf0,
  DIALOG 5/111 0xf6 @0xd14, VERSION 16/1 0x378 @0xe0c; LANG=0x409).
- Dir TimeDateStamp 0x33ef9c9b (root + all 9 subdirs) comes from CVTRES, i.e. the CLOCK at
  conversion: run cvtres frozen at `FAKETIME="@1997-08-11 23:13:31"` (**:31, one second
  before link's :32** — RC ran before LINK on the original box) → exact match; the per-dir
  version fields (root (0,4), type dirs (0,2), lang dirs (0,1)) also regenerated by cvtres
  automatically? NO — they come out right with our .res as-is (leaf lang 0x409, memFlags
  ignored); only ts needed the :31 freeze.
- Result (build/m0/FA.exe via `m0link3.rsp` = m0link.rsp + `FA.obj`, /OUT:FA.exe):
  ALL 6 sections byte-identical (.text/.rdata/.data/.idata/.rsrc/.reloc), section table
  equal, dir[0]=export dir equal. **Remaining deltas vs FA.EXE (all /DEBUG round):**
  1. dir[6] debug-dir: FA rva 0xe5000 size 0x54 — ours empty (need /DEBUG, see below).
  2. .reloc vsz 0x14354 vs FA 0x143d8 (+0x84) — link extends .reloc vsz to cover the MISC
     debug payload it writes into .reloc's zero tail under /DEBUG.
  3. File length: 0x131a00 (our .reloc raw end) vs FA 0x13e600 — FA appends the MISC/FPO/NB10
     debug payloads after .reloc raw (0xBC00 + more).
- /EXPORT probe reminder: /OUT basename becomes the export module name + export dir size —
  ALWAYS /OUT:FA.exe for real links (probe output "rsfull.exe" inflated dir[0] to 0x66).
- Repro pipeline (bash, from repo root):
  `python3 tools/mkrsrc.py FA.res && cp FA.res build/m0/`
  → docker cvtres (FAKETIME="…23:13:31") `CVTRES.EXE /machine:IX86 /readonly /nologo FA.res`
  → docker link (FAKETIME="…23:13:32") `LINK.EXE @m0link3.rsp` → compare
  `python3 build/m0/cmpexe.py FA/FA.EXE build/m0/FA.exe`.

### DIR32 fixup semantics (link 4.20) — probed (build/m0/d32.exe)
- Final image value = target_symbol_VA + baked 32-bit addend (addend = host obj's content
  dword). Verified with garbage addends: 0x11111111@_A0 → 0x11512111 = 0x401000+0x11111111 ✓.
- Identity scheme for stubs: host chunk zeroes each fixup dword; reloc DIR32 → target
  chunk's symbol; addend = FA_val − target_chunk_VA. No per-fixup symbols needed.
- FA fixup census (build/reloc_map.json): 39,401 HIGHLOW fixups — .text host 36,236
  (targets: .data 32,843 + BSS, .text 2,571, .idata 698 IAT slots, .rdata 124),
  .data host 2,997 (targets .data 2,450 incl BSS, .rdata 250, .text 297),
  .rdata host 168 (targets .data 120, .rdata 14, .text 34). All within [0x54,0x13f0) of
  .rdata; NONE in export dir/debug dir. .idata: 0 fixups (IAT never base-fixed).
- 12,288 targets land in .data BSS (RVA ≥ 0x122400): bss chunks need symbol stubs emitted
  as CNT_UNINITIALIZED .data contributions (raw 0, extends .data vsz only) — 550 stubs.
  117 of 251 .reloc blocks hold odd fixup counts (linker pads type-0 entries per odd block).

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

### 1. ✅ Fix `tools/peref.py main()` → emit `build/layout.json` (2026-10-31)
- Runs clean: FPO 2986 recs (0 overlaps); .text = 3834 chunks tiling 0xe3eec exactly
  (2986 fpo + 848 gap, 2413 named, 0 swallowed); .data = 1100 chunks covering 0xa2d98
  (1099 named, BSS tail handled via size_full vs size_file).
- Emits per-chunk `{name, va, rva, size, fpo, fpo_rec, off}` + section metadata,
  exports/imports/debug payload offsets into `build/layout.json`.

### 2. ✅ Obj-format ground truth → `tools/coff.py` (2026-10-31)
- Working COFF I386 obj writer mirroring cl's byte layout: section symbols w/ aux records,
  COMDAT `.text` + `.debug$F`, group objects (`build_group_obj`), relocation records.
- Exercised through all Milestone-0 probes (import-member archives, tail sweeps, stubs).

### 3. ✅ `tools/mkstub.py` — one obj per chunk (2026-10-31)
- Working: original bytes as section content, fixup relocations → containing-chunk symbols,
  `.debug$F` FPO records for fpo chunks, `.bss` groups, `.rdata` stub; mkrdata.py drives
  the whole stub set.

### 4. Milestone 0 — stub-only full link (the big gate) — ✅ COMPLETE (2026-10-31)
`sha256(atf95/Release/FA.exe) == sha256(FA/FA.EXE) ==
c7d2c1cc9d27a6b364eca4245892cb6ca61ca72afc9a46e5760ee1fe7d75ba9b` — byte-identical
including the /DEBUG debug payloads, verified on a fresh seed+link cycle. DONE:
direct `.idata$` group objs; fixup relocs in stubs; .rdata stub; .bss groups; .rsrc via
mkrsrc.py+CVTRES; /EXPORT:T_HorizonProc,WRFogLayerUpdate; /OUT:Release/FA.exe (cwd
E:\atf95 for the MISC "Release/FA.exe" string); frozen clocks; /DEBUG with .debug$S
modules + .debug$F FPO stubs (2986 plain records, no header — the payload header is
written by the linker).

**/DEBUG round findings (2026-10-31):**
- **Old-style (4.2-era) import libraries**: each import = full COFF obj member named
  `DLLNAME.dll/` with per-member sections `.debug$S`, `.text` (6-byte `ff 25` thunk + DIR32
  → `__imp__X@n`), `.debug$S`, `.idata$5` (IAT slot = hint|0x80000000, flags 0xc0301040),
  `.idata$4` (INT slot, same), `.idata$6` (u16 hint + name + NUL pad, 0xc0200040); per-DLL
  descriptor member (`.idata$2` + `__X_IMPORT_DESCRIPTOR`/`\x7fX_NULL_THUNK_DATA`) and an
  `.idata$3` NULL_IMPORT_DESCRIPTOR member. NOT needed for the build (we use direct
  `.idata$` objs) but documented for future tooling. Ground truth dumped from
  `vendor/MSVC420/lib/CTL3D32.LIB`, `KERNEL32.LIB`.
- **PDB-seed trick (this is how NB10 ts/age come out right)**: FA's CV payload = "NB10" +
  pdb_ts + pdb_age + path, FA ts=0x33ef9c68 (23:12:40 — PDB creation clock), age=1 but
  final link at 23:13:32. Sequence: delete `Release/FA.pdb`; run a THROWAWAY link frozen at
  `FAKETIME="@1997-08-11 23:12:40"` (creates the pdb, ts = link clock); delete the
  throwaway exe/lib/exp/map; run the REAL link frozen at `@1997-08-11 23:13:32` — LINK 4.20
  UPDATES the existing pdb preserving its ts and increments age to 1. Exe NB10 == FA's
  exactly. Reproduces from cold state (proven on 2 fresh cycles regardless of prior pdb age).
- **`.reloc` VirtualSize reserve delta (Δ=+0x84) — disposition**: LINK 4.20 under wine
  reserves an all-zero `.reloc` tail (VSZ past the fixup block content; FA extends VSZ over
  the MISC debug payload in that tail). Wine's reserve lands 0x84 below the 1997 NT build's.
  Probed exhaustively — option switches (/WS:RAM /WS /OPT:REF /OPT:NOREF /DEFAULTLIB /
  /SWAPRUN:CD,NET /RELEASE /IMPLIB /WARN), per-import counts and by-ordinal-vs-by-name
  import members (identical tail contribution), module counts, flavors — ALL zero effect on
  the delta. The tail bytes are all zeros on both sides and not mapped data, so
  `tools/fixreloc.py` forces VSZ=0x143d8 (header offset 0x248) post-link → image
  byte-identical, no load-time effect. Probe tools: `tools/sweeptail.py`, built libs via
  `tools/coff.py` group objects.
- Direct `.res` → LINK remains impossible under wine (LNK1104 TEMPFILE even with
  TMP/TEMP=Wine paths); keep running CVTRES ourselves.

**Canonical Gate-1 pipeline (repo root):**
1. `python3 tools/mkrdata.py` (emits stub/rdata/idata objs into `atf95/Release/`)
2. `python3 tools/mkrsrc.py FA.res && cp FA.res build/m0/`
3. docker CVTRES frozen `@1997-08-11 23:13:31` → `FA.obj` (`.rsrc$01`/`.rsrc$02`)
4. docker LINK frozen `@1997-08-11 23:12:40`, rsp `build/m0/m0link5.rsp` (SEED — creates
   `Release/FA.pdb`); `rm -f atf95/Release/FA.exe` + throwaway lib/exp/map
5. docker LINK frozen `@1997-08-11 23:13:32` same rsp (REAL — pdb ts preserved, age→1)
6. `python3 tools/fixreloc.py atf95/Release/FA.exe` (.reloc vsz → 0x143d8)
7. `sha256sum atf95/Release/FA.exe FA/FA.EXE` — must match `c7d2c1cc…ba9b`; then
   `cp atf95/Release/FA.exe build/FA.exe`
(Docker invocation quirks — `\\\\` rsp escaping, FAKETIME_DISABLE_SHM=1, no `head` —
see Phase 0 notes above.)

### 5. ✅ Phase 3 — workflow tooling (2026-10-31)
- `tools/gate.py` — Gate 1: sha256 vs FA/FA.EXE; on FAIL, every diff region is
  localized to section+rva and the symbol window from build/layout.json (tested on a
  deliberately corrupted copy).
- `tools/compare.py` — Gate 2: per-chunk (function-sized) match% of any candidate exe
  vs the original, only mapped file bytes (BSS skipped); first-diff rva per divergent
  chunk; `--json` for machine output. 3834/3834 text + 550/550 data identical on
  the Milestone-0 artifact.
- Link line remains: decompiled objs + stub objs in original address order;
  decompiled TUs must be address-contiguous runs (unchanged — enforced per-TU at
  Phase-4 pilot time).

### 6. Phase 4 — pilot decompilations — ✅ Pilots 1–7 PASSED, 7 swaps live (2026-11-01)
- **WRFogLayerUpdate @ 0xb06c0 (0x50 B)**: `src/WRFogLayerUpdate.c` — cl 4.2
  `/c /O2 /Gy /G5` reproduced FA codegen on the FIRST attempt (fastcall
  `Rand(51)` = `@Rand@4` resolves to the callee stub anchor).
- **StallSpeed @ 0x9b1f0 (0x30 B, cdwLocals=1, ret 4)**: `src/StallSpeed.c` —
  one byte of reconstruction: FA's source was `if (r <= 1)` (jg skip), not
  `<` (jge). Callee is UNNAMED (gap chunk 0xb0a0); fitobj `--map
  FROM=TO+delta` bakes the addend for INTERIOR targets: link 4.20 computes
  `final = sym + content − (site+4)`, so needed content = (site+4) − sym +
  FA_rel32.
- **WordToString @ 0x11780 (0x10 B)**: `src/WordToString.c` — fastcall→stdcall
  thunk (`push 0x20; push -1; push edx; push ecx; call _DoWordToString@16`);
  matched first try.
- **DialogSelectItem @ 0x87610 (0x90 B)**: `src/DialogSelectItem.c` — FIRST
  switch (8 cases) + first .data refs. Key steps to match FA codegen: case
  values map to 5 dedup'd jump-table slots (1,5→body1; 3→b16=1; 8→b30=1);
  default `goto`s the SHARED PopShellAlloc epilogue (past the firstDraw/
  DialogDraw check); callee SUB87070 is CDECL (FA has `add esp,4`) with a
  16-BIT param (avoids CL's redundant `xor eax,eax`); data refs resolve to
  real SMS symbol names (`?lastDial@@3PAUDIAL@@A`, `_firstDraw`) via
  fitobj `--map`. The 5-dword jump table + 8-byte index table sit INSIDE the
  text chunk at CL-identical offsets; CL bakes label-relative DWORDS with
  DIR32 relocs (final = sym+content) — remapping internal `$L*` labels by
  name works because the link resolves them to the chunk VAs. The 12 B
  beyond the tables (`05 00 00 00 00 8d a4 24 00 00 00 00`) are
  census-proven FA compiler filler (see docs/PATCH-FORENSICS.md): fitobj
  validates residue by full composition against the padcensus VOCAB table
  and copies it without any flag — the old per-case `--tail-accept` is
  retired.
- **Swap automation — `tools/swap.py` + `tools/swap.json`** (2026-10-31): the
  whole loop is now ONE command from repo root: `python3 tools/swap.py`
  [= compile + link + gate]. `swap.json` (version-controlled, in tools/) lists
  per-function entries `{rva, obj, src, flags?, maps?}`; steps `compile` /
  `fit` / `link` / `gate` runnable individually. Verified from a COLD
  Release/ dir (no FA.pdb) — the pdb-seed link cycle is handled internally.
  LINK rsp form: relative `'@..\\build\\m0\\m0linkD.rsp'` from docker cwd
  /work/atf95 (the absolute Z:\ form loses backslashes through the
  python→sh→docker quoting chain).
- **Swap mechanism** (all in tools/): C in `src/` → CL in docker →
  `fitobj.py <cl.obj> <rva> [--map FROM=TO[+addend]]` (FA tail pad + FA FPO
  record splice, drops `.drectve`) → `mkstub.py SPLIT_AT=<va>` singleton
  group → `mkrsp.py --replace <va>=<fit.obj>` → pdb-seed link cycle →
  `fixreloc.py` → `gate.py`.
- **Flag baseline for FA**: `/O2 /Gy /G5`.
- **carefulDiv @ 0xb5130 (0x80 B)**: `src/carefulDiv.c` — first x87 pilot
  and first NAKED decompilation. The chunk's prologue splits
  `mov eax,[esp+0x10]` between `push ebp` and `mov ebp,esp` (unreachable via
  C statements) and the chunk has NO FPO record ⇒ original is
  `__declspec(naked)`: whole body replicated verbatim in inline asm
  (fxam/fstsw classification vs g_divCls[], fld/fdivp, *out store, fild
  flag return). Const 1.0 maps to `$FA$rdata0+0x49c`; flag/res live inside
  the `?palColorRGB@@3UT_RGB@@A` BSS chunk (+0x44c/+0x440); the class table
  follows float `?rFloor@@3MA` (+4).
- **LibRead @ 0x78b50 (0xa0 B)**: `src/LibRead.c` — first LOOP/rep-movs pilot
  (loop = `memcpy` inlined by CL 4.2 /O2 as `shr 2/rep movsd/and 3/rep movsb`;
  the FA copy loop is just a variable-size memcpy call). cdecl
  `LibRead(short idx, void* dst, long max)`; fastcall MMLock(hintHndl,0) at
  entry (`xor edx,edx` = zeroed 2nd fastcall arg) + MMUnlock(hintHndl);
  record table = `?libAccess@@3PAULIBACCESS@@A`+4 (12-byte: start, pos),
  locked-region fields read at [ebp+eax+0x17/0x1b/0x1f]; final
  `pos += n` stores via the i3*4 offset kept in ebx. Codegen tells:
  - sib base order [ebp+eax*1+d] (FA) vs [eax+ebp*1+d] (CL) flips when p35
    is UNSIGNED and rc signed — mixed signedness blocks CL's commutative
    normalize;
  - `.start` needs `libTable[idx*3]` (scale form) while `.pos` needs the
    INDEPENDENT tree `idx*12` (forces `lea ebx,[edx*4]` + `[ebx+disp]`);
    naming one i3 variable CSEs both into scale form (3-byte mismatch);
  - `s * 7 * 5` keeps FA's two-step lea chain (*7 then *5) for *35;
  - CL always fuses `*(long*)(p35+rc+0x1f)` into a sib while FA materializes
    `lea ecx,[ebp+eax]` + `[ecx+0x1f]` (+3 B), and CL hoists the MMUnlock
    arg reload (`mov ecx,[hintHndl]`) ~13 insns early vs FA's just-before-
    the-call — two scheduler choices our CL 10.20.6166 does not switch via
    source or flags (hunt 2026-11-01: 11 source variants byte-identical, 20
    flag sets artifact-/G5-only with FA's shape unmatched, TU context null;
    see docs/PATCH-FORENSICS.md). Classified **toolchain-diff**
    (revision-attributed, NOT "provably immovable" — TODO previously
    overstated this): the 9-byte `--patch` repair stays, with its
    classification recorded in swap.json `provenance` and enforced by
    `tools/swap.py audit` (nonzero on unexplained; gate precondition).
- **StartGameThread @ 0x35e50 (~0x80 B, 3 chunks)**: `src/StartGameThread.c` —
  first SEH pilot AND first pilot whose swap was verified LIVE (the exe
  actually contains compiled decompiled code, not stub bytes). It is a C
  `__try`/`__except` function — FA has NO C++ throw sites at all (no
  `RaiseException` import; every try frame pairs with `__except_handler3`),
  so the "throw-site C++ member" pilot premise is retired. Codegen tells:
  the SEH prologue is fully INLINED by CL (set frame + `[ebp-4]`
  __except_handler3 ptr + `mov eax,fs:[__except_list]` + push tryscope +
  push handler3, then `mov [ebx-4],ecx`-style context slot `[ebp-0x14]`
  written by handler3); FA's filter inlines `GetExceptionInformation()` as
  `mov eax,[ebp-0x14]` while our first source emitted an `e8` helper call —
  ROOT CAUSED and ELIMINATED (2026-11-01, docs/PATCH-FORENSICS.md):
  `#include <excpt.h>` expands the macro to
  `(struct _EXCEPTION_POINTERS*)_exception_info`, an intrinsic inside a
  `__except` filter that CL inlines to FA's exact bytes; the include also
  renames CL's scope-table symbol `$T107`→`$T121` (same `.rdata` anchor,
  swap.json map updated). GATE 1 PASS with zero StartGameThread patches.
  `_g_filterFn` (the ind-
  irection FA's filter reads) is the named data chunk `_overflow_ptr`
  @ 0x586228; FA's own filter is a plain null filter = `_unknown_divide_error`
  @ 0x4bb200.
- **Span mechanism (multi-chunk functions)**: CL/FA split `__try` functions
  into units over several chunks (main 0x35e50 + filter 0x35e9d + handler
  0x35eab). New `SPLIT_SPAN=VA:SIZE` (mkstub: one merged singleton group,
  inner chunks' anchors re-defined as offset aliases) + fitobj `--span SIZE`
  (FA bytes concatenated across the run, chunk tiling asserted) +
  `--alias OFF=NAME` (fitted obj re-defines the inner anchors so .rdata
  scope-table funclet pointers resolve). swap.json keys: `span`, `aliases`.
- **Critical pipeline bugs found & fixed (first LIVE link)**:
  - **Silent-noop RVAs-vs-VAs**: swap.py passed RVAs to SPLIT_AT/--replace
    (VA-form keys) — since pilot 3 every committed Gate-1 PASS was a no-op
    (stub code linked, fit objs ignored). Fixed by +IMAGE_BASE everywhere;
    always confirm a swap is live by a link that FAILS when the fit obj is
    excluded (the silent-noop era passed trivially).
  - **COMDAT dedup trap**: fitted `.text` carried cl's COMDAT flags keyed on
    the generic `.text` symbol — link 4.20 dedups ALL same-keyed COMDAT
    sections, silently dropping every fitted obj after the first
    (LNK2001 for later objs' definitions). Fitted `.text` must be PLAIN
    0x00100020 (microtest: build/mt7).
  - **Lnk2001 shadow twins**: build_stub_obj created undefined externals for
    reloc targets even when more_syms re-DEFINED the same name (cl-internal
    `$L*` labels) — relocs bind to the undefined index. Fixed: defined
    more_syms that are reloc targets are added early and reused.
  - **FPO payload conservation**: the stub singleton carried FA's .debug$F
    for span chunks; the fit obj must re-emit a .debug$F per chunk whose
    (rva,size) is in FA's payload (fitobj now copies mkstub.fa_fpo_records).
    One missing record shifted the payload AND the debug-dir SizeOfData/ptr.
  - **Wine exit-code lie**: LINK reports LNK1120 with exit 0 — success check
    is `FA.exe` existence, not `echo exit=0`.
  - **Double-based anchor names**: `$FA$_t_4087070`-style (VA of an already-
    VA'd base) must be `$FA$_t_487070` (rva 0x87070 + 0x400000) — bit us
    twice (pilot 4 map + pilot 7 aliases).
- Remaining pilots: scale up to bulk decompilation.

### 7. Phase 5 — hardening
- Progress tracker JSON (N/3829 functions), CI gate, update `MSVC_VERSION.md` with the
  empirically resolved 4.2 vs 4.2b revision.
- DONE 2026-11-01: bulk-decompilation tooling — `tools/sites.py` (+ `dis.py`
  annotated-disassembly, `mapgen.py` map autogen, `rank.py` easiest-first
  selector + `tools/progress.json` tracker; validated 7/7 pilot site tables,
  18/18 pilot map lines VA-covered), and `swap.py compile` batching (one
  container, `__OK__/__FAIL__` markers; CL objs vs per-entry path differ only
  in the header-timestamp field, fit objs byte-identical, GATE 1 PASS).
  Note: selector was named `rank.py` — never `select.py` (shadows stdlib
  `select` and breaks `subprocess`). Known scorer blind spot: scheduler-level
  revision patches (LibRead-style) are invisible statically — check the seh/jt/
  fixup columns and TODO Phase 4 tells before committing to a "cheap" target.
- DONE 2026-11-01 — WAVE 1 (first selector-driven batch): 8 easiest-first
  leaf functions swapped (LockExit 0xd3970, UnlockExit 0xd3980, Errno
  0xd99b0, CExit 0xd3890, GetMbcp 0xd9e20, GetSbhThreshold 0xddfc0,
  Localeconv 0xe1ec0 — all 6-11 B — and LibraryStartup 0x117b0), 80 B,
  GATE 1 PASS. New tells:
  - **Moffs-load form**: FA's `a1 <abs>` loads reproduce from a plain
    `*(int *)(extern_array + CONST)` — CL bakes the constant disp as the
    reloc'd content dword (DIR32), symbol = the named data chunk extern,
    NO map needed. All three getters matched first try.
  - **Map FROM keys are RAW obj symbol names**: C id `_doexit` emits the
    obj symbol `__doexit`; a map keyed `_doexit=` silently does not match
    and the external stays referenced (LNK2001 at link, not at fit). The
    C-underscore-prepending rule applies to every hand-written map.
  - Void cdecl tail calls CANNOT fold to jmp (caller cleans), so the
    push/call/add-ret shape reproduces naturally; no prologue needed for
    FPO cbProlog=0 leaves.
  - Next band (diff 4): the 16-B fastcall MM* wrapper family
    (@MMAllocPtr@8, @MMLock@8, ...) — wave 2 material.

---

## Verification invariants (every handoff step)
1. Two identical builds (frozen clock) before trusting any diff.
2. Gate 1: `sha256(build/FA.exe) == sha256(FA/FA.EXE)` on every commit.
3. No third-party static code assumed in the EXE beyond CRT (audio/CD/net live in DLLs).