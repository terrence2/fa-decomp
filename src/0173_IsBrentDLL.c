// ?IsBrentDLL@@YIDPAX@Z @ rva 0x1e430 (123952, 22 B code + 10 B pad) —
//   fastcall int(void *p): memcmp(p, brentDLLName, 0x1c) == 0 as an inline
//   repz cmpsb (56/57/8b f1/bf imm32/b9 1c/f3 a6/0f 94 c0/pop/pop/ret):
//   FA streams NO xor eax,eax before the sete; CL inserts 33 c0 at 0x1
//   (its int-return zero-extension rule) — the 2-B delta is the only
//   difference.
// patch-hybrid (survey tier-1, 1 patch): plain C with #include <string.h>
//   lets CL 6166 emit the intrinsic repz-cmpsb expansion byte-for-byte
//   (memcmp == 0; earlier naked note "CL emits a memcmp call" applies to a
//   different revision/spelling — with the constant size and /O2 /G5 it
//   inlines).
//   patch 0x1: delete 33 c0 (CL's int-return zero-extension before sete
//     al) — root-caused: CL 6166 zero-extends every int return expression;
//     FA's revision leaves eax's upper garbage per the sete-al-only form.
//     Deleting 2 B shifts the bfimm32 d32 reloc (0x7) -2 automatically.
//
// probes: build/survey/probes/t1_brent_v1.c (EXACT via patch), _v2.c/_v3.c
//   (no) — run: python3 build/survey/hybrid_probe.py ... then
//   python3 tools/fitobj.py build/survey/probes/t1_brent_v1.obj 123952
//   --map ... --patch '0x1,2,'
//
// maps VERBATIM: _brentDLLName=?setSoundAndMusic@@3JA+0x6c
// entry: add "patch": ["0x1,2,"]  (provenance: 'patch 0x1: root-caused —
//   CL int-return zero-extension 33 c0 before sete al; FA has none')
#include <string.h>
extern char brentDLLName[];  /* map: _brentDLLName=?setSoundAndMusic@@3JA+0x6c */

int __fastcall IsBrentDLL_q(void *p)
{
    return memcmp(p, brentDLLName, 0x1c) == 0;
}