# Probe plan: converting asm-escape functions back to real C

Execution order = cheapest-first; every experiment runs through
`build/survey/hybrid_probe.py` (config JSON of swap-shaped entries + flags;
compiles in docker batches, fitobj-judges, verdicts EXACT/no). Probe sources
live in `build/survey/probes/<fn>_v<k>.c` — build/pilot/ stays clean.

## Tier 0 — elision/bare re-read (no C creativity needed)

Files where the REASON was an incomplete disassembly or nothing:
MaxSpeed, MISSIONSetCheating, AlmostHome, get_pkt_err_string,
_line_overflow1, CDirDrawSurfaceUnlock, HARDNumLoaded, SetScenarioEndTime,
CTDo_exit, OBJStopAdding, G_StringWidth, IsZeroMan, EnvHighest,
PLANEUpdateJustLanded, FcloseLk, G_HFlipBitmap, G_SetHShake, GToTurn,
everyoneHasChosenSides, do_start, unexpected, heap_term.

Method: re-disassemble the chunk from raw bytes (objdump_text.py /
compare.py), verify every instruction is accounted for (c7 05/c6 05 stores,
66-words, sib forms), THEN either re-C or record the true reason.
Success: fitobj EXACT.

## Tier 1 — rep-block intrinsic re-probe

Hypothesis H2: an asm block containing rep/stos/scas/movs that FA plausibly
got from a CRT expansion. `#pragma function(name)` list per candidate:
- `__strcats` (reg-plan class but body is strcats chain) → probe
  plain-call `strcat` spellings + `#pragma function(strcat)`.
- `MISSIONEnsureLegalName` — the `repne scasb` strlen → try
  `strlen` call + `#pragma function(strlen)` + lever matrix below.
- `fread`/`fwrite`/`fprintf` wrappers — rep movsd loops → memcpy-style
  expansions with `#include <stdio.h>` semantics as CL saw them.

## Tier 2 — lever matrix (reg-plan + scheduler classes)

Hypothesis H1. The six proven levers, applied systematically (each probe =
one lever toggle; 2^k capped at 8 variants):
1. **first-decl**: contested local declared FIRST (CopyMan d180 proof).
2. **push-slot**: independent store placed in the call's arg-push
   statement position (CTInit d126 proof).
3. **live-across-call**: contested value written in the argument
   expression itself, not a preceding statement (HUDReprintMessages).
4. **guard-init**: initialization inside the if-guard (StreamersShutdown).
5. **tree-split**: CSE-sensitive repeated subexpressions written as
   independent trees, not shared local (LibRead .start/.pos proof).
6. **polarity**: ternary → explicit early-if guard form (wave-2 tell);
   plus operand-mirrored compare direction when FA streams reversed.
Extra axes where relevant: narrow vs wide local type (char/ushort/ulong
mask steering, wave-21), volatile (double re-store, wave-18).

Candidates (reg-plan class first):
MISSIONEnsureLegalName, StringForLanguage, WrapHB, G_HFlipBitmap,
G_CopyDriverName, G_ColorStringWidth, ChangeTint, Fclose, EnvHighest,
G_DrawYLR, VIEWInTransition, fread, fwrite, fprintf, __strcats, nh_malloc,
get_osfhandle, RotatedOffset, MaybeCallEventProc, COThrust, ValidateRead/Write,
SampleUpdate, dlg_list_clear, NPCSetStateTarget;
scheduler class: PutCurObj, InBounds, SampleUpdate, __abnormal_termination,
COThrust, do_setlight, APGetPark, InsectWingAngle, Ui64toa, InBounds3.

Success criterion: fitobj EXACT (no --patch), then fold into swap.json as
a wave batch with full from_sweep --objcheck + GATE 1.

## Tier 3 — patch-hybrid sweep (MASM-encoding class)

For the 80-file class: if a 1–3 B delta separates the CL spelling from
FA's, write plain C + accept a small patch (precedent: PopCurObj 1 B,
VIEWChangeObj 6 B, FillZeroMan). Only after Tier 2 exhausts spelling.
Each patch needs root-cause provenance in the audit contract.

## Tier 4 — per-TU flag axis

For every function still stuck after 1–3: rebuild the SAME plain-C source
under the ~20-set flag matrix (lrflags.py sets: /O1, /Os, /Ow, /Ob1, /Ob2,
/Og-, /Oi-, /Oa, /Gs, /Gs0, /Gf, /G3, /G4, /Ga, /Gd, /Gi, /Gx, /Gz, /Gr,
/QIfdiv, /QI05), via hybrid_probe.py "flags" per entry. CRT-band files
first (Microsoft's originals were plausibly not /O2 /G5: /O1 = /Gs+/Os+
/Gf+/Gy). Land any EXACT via the entry "flags" key.

## Keep-asm (do not spend effort)

thunks (209), SEH/NLG/_emit (14), gap anchors (11), x87 (6: __ftol,
control87, Statusfp, Clearfp, GRSinCos, CarefulDiv), CC-structural
(xchg+jmp Members 0-2, GG_WaitRetrace thiscall push-1, FPSPrint esi-param),
dllimport shapes (9).