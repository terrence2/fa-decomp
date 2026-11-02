// _HARDGunsOnlyAll@0 @ rva 0x52a60 (338528 DEC; off 335456) (80 B) — EXACT
// winner (probe w24c_HARDGunsOnlyAll_v1.c, first probe). Pure CL C, NO
// patches. 0x49 body identical + census tail 8da42400000000 (7 B).
//
// FA asm: push ebx/esi/edi / mov esi,1 (i=1 — 32-bit init even though the
// uses below are 16-bit) / cmp word ds:[_nextObjId],si / jbe epilogue
// (unsigned entry guard) / mov edi,esi (m = i — the copy from esi is why
// m's value comes from i, not a bare constant) / mov ebx,4 (t) / loop:
// mov ecx,esi / call @GetCurObj@4 / test ds:[_curThing+0x1],edi (mem-op
// bit test against the mask reg) / je skip / mov al,ds:[_curThing] /
// cmp al,bl / jne skip / call _HARDGunsOnly@0 / skip: inc si (16-bit!) /
// call @PutCurObj@0 / cmp word ds:[_nextObjId],si / ja loop; pop edi/esi/
// ebx; ret.
//
// C recipe — the types drive everything:
//   - i, m declared `unsigned short`, t `unsigned char`: i's 16-bit gives
//     the 66 39 35 word compares and the 66 46 inc si; m's ushort+`m = i`
//     gives mov edi,esi; t's uchar with `t == *(char *)&curThingQ[0]` gives
//     mov al,[g] / cmp al,bl (bl = low byte of t's home ebx).
//   - `m = i` (not m = 1): the FA copy from esi comes exactly from
//     assigning m from i inside the guard.
//   - GetCurObj_q's param declared `unsigned short` — fastcall mangles
//     chars/shorts as 4-byte dwords (@4) and passes the raw register with
//     no widening (mov ecx,esi, stale uppers ride).
//   - `*(unsigned long *)&curThingQ[1]` = dword field at _curThing+0x1;
//     CL emits test ds:[g],edi with the mask in edi (mem first operand).
//   - `if (nextObjId > i) { ... do ... }` with the SAME condition as the
//     do-while back-test (both unsigned ushorts, jbe/ja).
//
// Maps (obj FROM -> FA name): _curThingQ=_curThing (sites +0x1 interior and
// +0x0 identity), @GetCurObj_q@4=@GetCurObj@4, @PutCurObj_q@0=@PutCurObj@0,
// _hardgunsQ=_HARDGunsOnly@0 (FA keeps the bare C name _HARDGunsOnly@0).
// _nextObjId is an identity anchor (declared extern unsigned short).
//
// Fit line:
//   python3 tools/fitobj.py build/survey/probes/w24c_HARDGunsOnlyAll_v1.obj 338528 \
//     build/survey/probes/w24c_HARDGunsOnlyAll_v1_fit.obj \
//     --map '_curThingQ=_curThing' --map '@GetCurObj_q@4=@GetCurObj@4' \
//     --map '@PutCurObj_q@0=@PutCurObj@0' --map '_hardgunsQ=_HARDGunsOnly@0'
extern char curThingQ[];   /* _curThing */
extern unsigned short nextObjId;  /* _nextObjId */
extern void __fastcall GetCurObj_q(unsigned short idx); /* @GetCurObj@4 */
extern void hardgunsQ(void); /* _HARDGunsOnly@0 */
extern void __fastcall PutCurObj_q(void); /* @PutCurObj@0 */

void __stdcall HARDGunsOnlyAll_q(void)
{
    unsigned short i = 1;
    unsigned short m, t;
    if (nextObjId > i) {
        m = i;
        t = 4;
        do {
            GetCurObj_q(i);
            if (*(unsigned long *)&curThingQ[1] & m)
                if (t == *(char *)&curThingQ[0])
                    hardgunsQ();
            i++;
            PutCurObj_q();
        } while (i < nextObjId);
    }
}
