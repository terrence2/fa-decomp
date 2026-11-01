# Patch-site forensics: how FA.EXE got its bytes

Every deviation our toolchain needed to reach byte-identity (a `fitobj
--patch` directive, a tail pad we couldn't explain, a helper call where FA
inlines) is inventoried here with its root cause. The regression that keeps
this honest: **`python3 tools/swap.py audit`** — every entry in
`tools/swap.json` carrying `patch` or `tail` sites must classify each one
(`root-caused` / `toolchain-diff` / `unexplained`) in its `provenance` key,
and `audit` exits nonzero on anything `unexplained` or left without a
classification. It runs as a **gate precondition** (`swap.py gate` calls it
first), so an ad-hoc patch can never pass silently again.

Forensics ran 2026-11-01 (this document supersedes the interim
"provably immovable" wording in TODO.md's pilot-6 notes).

## Shared findings (they answer several sites at once)

### 1. The filler table (Workstream A — `tools/padcensus.py`)

Census over all 2986 FA FPO-record extents (`python3 tools/padcensus.py fa`):

- **Inside-record tails** (compiled filler, counted in `cbProcSize`): 2384
  pad regions, every one decomposing into the VOCAB token table. Gap-to-16
  maps cleanly: 1→`90`; 2→`8b ff`; 3→`8d 49 00`; 4→`8d 64 24 00`;
  5→`05 00 00 00 00`; 6→`8d 9b 00 00 00 00`; 7→`8d a4 24 00 00 00 00`;
  8..15 → concatenations, always **shortest-first** (e.g. 12 =
  `05 00 00 00 00` + 7B lea; 13 = 6B + 7B; 11 = 4B + 7B; 2×7 = `8d 64 24
  00 8d 64 24 00`? — no: observed 8 = 4B+4B, 15 = 4B+4B+7B).
- `05 00 00 00 00` (`add eax,0`) is genuine FA-compiler filler, 334+ sites
  of the 6-byte `lea ebx,[ebx+0]` form likewise, and FA also aligns
  loop/branch targets mid-function with the same table.
- **Between-record regions** (418): all 0xCC runs or genuine code between
  non-FPO functions — *linker* padding, which our LINK 4.20.6164
  reproduces (`build/probe/pads/mkprobe2.py`: probe2 shows LINK pads 0xCC
  between align-16 sections, aligns nothing under align-1, regardless of
  `.debug$F`). **Hypothesis "the linker inserts lea-family filler" is
  dead.**

Consequence: tail residue that decomposes into this table is *proven* FA
filler; `fitobj` now validates residue by full composition (not a loose
byte-set) and copies census-proven pads **without any flag**. The per-case
`--tail-accept` for DlgSel and CarefulDiv is retired (`"tail": true` keys
removed from `tools/swap.json`).

### 2. The CL revision gap (Workstream C evidence, cross-workstream)

CL 10.20.6166 in the container differs from FA's CL in **/G5-family
scheduler/register-allocation behavior**. Two independent fingerprints:

- Pad policy: FA's CL emits the VOCAB filler inside `cbProcSize`; ours
  never does under 20 flag variants (`build/probe/pads/lrflags.py`,
  battery + flag sweep), while LINK-side 0xCC matches ours exactly.
- Scheduler shape: the LibRead artifacts below appear under every /G5
  source form we tried but with different placement than FA's.

Negatives from the LibRead hunt are therefore **revision-attributed**, not
"provably immovable": a different 4.2 revision could plausibly reproduce
FA's bytes; we just can't (VC5's CL is not in the container; no second 4.2
revision has surfaced).

## Per-site table

| # | Site | FA bytes / deviation | Mechanism ("how FA got it") | Evidence experiment | Final state |
|---|------|----------------------|-----------------------------|---------------------|-------------|
| 1 | DlgSel tail @ 0x87610+0x84 (12 B) | `05 00 00 00 00` + `8d a4 24 00 00 00 00` | FA compiler pads the function to 16 with VOCAB filler (5B+7B, shortest-first), counted in cbProcSize | Census: 187 occurrences of exactly this composition; battery: our CL emits none | **explained** — composition check, no flag (2026-11-01) |
| 2 | CarefulDiv tail @ 0xb5130+0x7b (5 B) | `05 00 00 00 00` | same (5B token) | Census x168 of exact composition | **explained** — composition check (2026-11-01) |
| 3+6 | LibRead 0x39 / 0x4d (hintHndl reload placement) | FA hoists load ①early then loads a **2nd** time late (@0x4c, between f3-load and `03 ea`); CL 10.20.6166 puts both loads early | FA's cl revision schedules the MMUnlock argument load at the call | 11 source variants (`lrsweep.py`: volatile, hoist-var, post-access, ptr-fusion) all byte-identical; 20 flag sets (`lrflags.py`): artifact only under /G5-family, and FA's shape matches none; TU context (neighbor pressure, `#pragma optimize`) no effect | **kept**, classified `toolchain-diff` |
| 4+5 | LibRead 0x44 / 0x4a (fused f3 sib) | FA materializes the address (`8d 4c 05 00` lea ecx,[ebp+eax] + `8b 69 1f`); CL fuses `8b 6c 05 1f` | Same scheduler revision; struct-with-declared-offsets is impossible — FA's field offsets 0x17/0x1b/0x1f are not 4-aligned | Same sweeps; struct form rejected on padding | **kept**, classified `toolchain-diff` |
| 7 | StartGameThread filter funclet @ 0x4b (was 55→53 B patch) | FA inlines `GetExceptionInformation()` as `mov eax,[ebp-0x14]`; our first source emitted `e8 __GetExceptionInformation` | **Root cause found**: src omitted `#include <excpt.h>` → implicit decl → C4022 helper call. EXCPT.H expands the macro to `(struct _EXCEPTION_POINTERS *)_exception_info`, which CL treats as an intrinsic inside a `__except` filter and inlines — FA's exact bytes. Include also renames CL's scope-table symbol `$T107`→`$T121` (same `.rdata` anchor, map updated) | `#include <excpt.h>` + full pipeline; GATE 1 PASS with zero StartGameThread patches | **eliminated** (2026-11-01); `patch: []`, history kept in `provenance` |

## What the audit enforces

```
$ python3 tools/swap.py audit
  LibRead   patch[0]   toolchain-diff: patch 0x39/0x4d (hintHndl reload placement): ...
  ...
  ok: 4 site(s) classified, 0 unexplained
```

- Every `patch` directive and `tail` acceptance needs a matching
  `provenance` string in its swap.json entry (`patch <offs>: <state>:
  <evidence>`, directives may be grouped by offset; `tail: <state>: ...`).
- A provision left `root-caused` while its directive is still applied
  fails (stale patch = remove it from swap.json).
- `unexplained` / missing classification ⇒ nonzero exit ⇒ gate fails.

## Residual risk (honest accounting)

The two LibRead classifications rest on exhaustive negative evidence under
CL 10.20.6166, not on reproducing FA's compiler. If a second 4.2-era CL
revision ever becomes available, sites 3–6 are the first thing to re-try
(the sweep harnesses are one command: `python3 build/probe/pads/lrsweep.py`,
`python3 build/probe/pads/lrflags.py`).