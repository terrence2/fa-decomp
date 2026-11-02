# Survey tier-0 results: 2026-11-01 (25 re-C, 13 KEEP-ASM, GATE 1 PASS)

Probe ladder executed per `probe_plan.md` via `hybrid_probe.py`. Three parallel
batches on disjoint bands; every EXACT conversion re-judged from the final
`src/` file sitting in the repo, then merged through the standard pipeline
(targeted CL compile → `swap._fit` → `from_sweep.py --objcheck` → full
`swap.py link gate`). **936 entries, GATE 1 PASS** (exe sha
c7d2c1cc…ba9b). Probe configs + variant sources:
`build/survey/probes/{tier0_r1..r8,bm_band1..8}.json` / `*_v<N>.c`.

## Conversions

### Batch A — bare-header/early-wave band (12/17)

| file | rva | verdict | decisive lever |
|---|---|---|---|
| HARDNumLoaded | 0x530e0 | C | `& 0x7fff` on an **unsigned long return** (forces CL out of the and-ax narrowing; 32-B `25 ff 7f 00 00` like FA) |
| SetScenarioEndTime | 0x63800 | C | scalar **ushort externs** (66 add cx,[mem] form) + guard polarity `end > v` |
| CTDo_exit | 0x64bf0 | C | **named volatile local** (load/or/store triple) — expression-instant volatile still fuses to `or [mem],al` |
| OBJStopAdding | 0x8f480 | C | globals declared as plain values (pointer/array externs add a deref CL FA lacks) |
| G_StringWidth | 0x96b20 | C | none — chunk was simply never probed |
| G_SetHShake | 0x97330 | C | two **separate ifs** for the shared guards (combined && merges FA's two tests) |
| PLANEUpdateJustLanded | 0x9dd60 | C | none (uchar params) |
| heap_term | 0xdc1c0 | C | **first-decl register lever**: `h` declared before the fn-ptr parks esi=h/edi=IAT → `call edi` |
| GToTurn | 0x75970 | C | high clamp **falls through** (`if (r>10240) r=10240; return r;`); early-return/ternary make CL ecx-save r |
| G_GetPoint | 0x95880 | **patch-hybrid** (1) | CL folds load+add-once into `add esi,[eax+0xa]` (03 70 0a) when base reg dies — 10 spellings incl. named volatile all fold |
| G_HFlipBitmap | 0xb4cc0 | **patch-hybrid** (3) | hoisted base load + role/multiply order; region patch 14→12 B + 2 jcc disp repairs |
| EnvHighest | 0x9b4f0 | **patch-hybrid** (10, same-len) | /G5 register-role swap + CL compare-polarity normalization; operand mirroring does NOT steer |

### Batch B — elision/MISSION band (5/8)

get_pkt_err_string, MISSIONSetCheating, AlmostHome, _line_overflow1 (all
plain C after the tier-0 elision re-read — abandoned on incomplete
disassembly), CDirDrawSurfaceUnlock (plain C).
KEEP-ASM: MaxSpeed (case-7 stack-arg interleave + movsx tail),
MISSIONEnsureLegalName (p/s register homes swapped + 3-B dead-lea CSE),
MaskEvents (CL never keeps a partially-byte-written 16-bit value in AX →
`and al,0xfe` (24 fe) unreachable, length-changing patch impossible).

### Batch C — CRT reg-plan band (8/13)

| file | rva | verdict | decisive lever |
|---|---|---|---|
| fread / fwrite | 0xd5680/0xd5810 | C | esi/edi plan falls out of natural C — old arg-shuffle conservatism |
| RotatedOffset | 0x11aa0 | C | claimed "shift-in-ecx/raw-in-eax split" reproduces from plain C |
| COThrust | 0x77060 | C | fold the three guards into one `&&` chain |
| InBounds | 0x11b90 | C | lazily-computed 2nd dword **inside the 3rd/4th \|\| operands** gives FA's delayed [eax+8] load |
| nh_malloc | 0xd92b0 | C | else-branch `pv = 0` forces the loophead re-init (b8 imm32); `return pv` (not `return 0`) gives FA's je-to-exit |
| fprintf | 0xd5ce0 | C | FA's "odd push edi/esi reserve slot" = CL deferring the edi save into the **arg-push stream**; esp offsets self-balance both ways. FA's dopr arg order is (stream, fmt, arglist) — the old note read push order as arg order |
| PutCurObj | 0x61b40 | C | **inline the subscript into the memcpy call** (local `d` form differs only at FA's lone nop) |

New idiom (batch B): `&`-of-mapped-symbol store form gives `c7` mem-imm32 + HIGHLOW; uchar/short return types give b0/32 result forms; success-as-if-arm polarity gets `goto fail` inlined.

## KEEP-ASM verdicts (13) — the walls, precisely

| file | rva | wall |
|---|---|---|
| MaxSpeed | 0x76c20 | case-7 stack-arg interleave + movsx tail (8 probes) |
| MISSIONEnsureLegalName | 0x84a60 | p/s register homes swapped; mov-al vs mov-cl reload; 3-B dead-lea CSE artifact (6) |
| MaskEvents | 0x63060 | partial-byte-write 16-bit value in AX unreachable in CL (6) |
| MaybeCallEventProc | 0x62b40 | FA 16-bit stack-slot load `mov dx,[esp+4]` (66 8b 54 24 04) — CL never emits 66-prefixed slot loads, always 8b 44 24 04 + 25 ff ff 00 00; + reg swap in the call push pair (8) |
| get_osfhandle | 0xdec90 | FA direct mem bit-test `f6 40 04 01` vs CL materialized mov bl/test bl; cmp mirror unsteerable both directions (8) |
| ValidateRead/Write | 0xdf480/0xdf4a0 | FA interleave p1-push/mov/p2-push (FPO cbRegs=1) vs CL push ebx+esi, cbRegs=2; push-slot order compiler-revision (8/7) |
| __strcats | 0xd7ac0 | count re-read from memory EVERY iteration (inc/cmp [esp+0x18]/jl) — CL always caches in a reg; scasb/movsd kernel itself is byte-EXACT (8) |
| IsZeroMan | 0xdfa40 | load-folds-to-test `cmp dword [ecx],0` (83 79 00) vs CL load-then-test (4) |
| FcloseLk | 0xd3f50 | same wall at byte width: `cmp byte [esi+0xc],0x83` (f6 46 0c 83) vs byte-load+and (3) |
| unexpected | 0xdf3e0 | TLS slot `cmp dword [eax+0x64],0` vs CL load-then-test (4) |
| EveryoneHasChosenSides | 0xa24c0 | CL re-materializes a global in the loop-bottom test even with a local cache `n` (39 05 / 7f ed) (7) |
| do_start | 0xd0604 | code begins `56 c3` — a stack-argument shim with no C form (disassembly verdict) |
| CRT wrappers (heap_term siblings) | — | covered by tier-4 flag axis as future work |

## New survey-wide conclusions

1. **Wall families collapse to three**: (a) load-folds-to-test at mem operands
   (IsZeroMan/FcloseLk/unexpected/get_osfhandle — CL 10.20.6166 always
   materializes first), (b) 16-bit/interleave stack-slot forms CL never emits
   (MaybeCallEventProc/ValidateRead/MaskEvents/MaxSpeed), (c) global
   re-materialization/CSE artifacts (EveryoneHasChosenSides/MISSIONEnsureLegalName).
2. **Named volatile** is the only volatile form that forces a real load — but
   it still cannot prevent the load-then-test peephole.
3. **Compare-direction mirroring is NOT a lever** in this CL revision (EnvHighest
   both directions) — unlike the old ternary-polarity tell.
4. The real suspicious-asm population is now **~13/936 (<1.5%)** by probe
   evidence: the survey's ~80 estimate was itself conservative.
5. Remaining ladder: tier-1 intrinsic re-probe (rep-blocks), tier-4 per-TU
   flag axis on the CRT band, and the MASM-encoding class (80 files) is
   mostly SEH/thunk/keep-asm per reasons.json — re-triage before investing.