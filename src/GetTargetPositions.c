// @GetTargetPositions@4 @ rva 0x13f10 (81680 DEC; off 78608) (80 B) — EXACT
// winner (probe w24c_GetTargetPositions_v5.c). Pure CL C. NO maps, NO
// patches — all four externs are identity FA anchors (obj _numVisibleTargets,
// _visibleTargetIds, _objPtrs, _GRTo2d@8).
//
// FA asm (72 B body + census tail 2x8d642400 = 8 B):
//   push ebx / mov eax,ds:[_numVisibleTargets] / push esi / push edi /
//   xor esi,esi (i=0) / cmp eax,esi / jle exit (entry guard, do-while
//   rotation) / mov ebx,_visibleTargetIds (pw init INSIDE the guard) /
//   mov edi,ecx (pd = pos, deferred copy) / loop head = push edi (arg2
//   pushed raw, right-to-left) / xor eax,eax + mov ax,[ebx] (16-bit id
//   load) / mov eax,[eax*4+_objPtrs] (scaled index) / add eax,0x11 /
//   push eax (arg1) / call _GRTo2d@8 / test eax,eax / jge +5 / mov word
//   [edi],0x8000 / add ebx,2 / add edi,4 / inc esi / mov eax,ds:[_nVT]
//   (global reload after call) / cmp eax,esi / jg loop; exit: pop edi/esi/
//   ebx / ret.
//
// COLORING LEVER (the hard part): CL 4.2's register assignment for the
// three locals follows DECLARATION order — `unsigned short *pd, *pw;` (pd
// declared before pw) with pw initialized first inside the guard gives
// pw=ebx/pd=edi/i=esi exactly FA's coloring. Every other spelling tried
// (v1 param used directly: pw=edi/pd=esi/i=ebx before the test; v2 i first
// + pw cond: pd=esi/i=edi/pw=ebx; v3/v4 pw declared first: pw=edi/pd=ebx)
// mismatches. Assignment order within the guard (pw=imm32 THEN pd=ecx copy)
// does not affect coloring, only declaration order does.
//
// Idiom notes: *pd = 0x8000 as unsigned-short store emits 66 c7 07 0080;
// (int)objPtrs[*pw] emits the xor eax,eax+mov ax,[ebx] 16-bit load and the
// mov eax,[eax*4+imm32] scaled index; pd += 2 on an unsigned short * emits
// add edi,4; GRTo2d's (int, ptr) args push right-to-left with pd pushed raw.
//
// Fit line:
//   python3 tools/fitobj.py build/survey/probes/w24c_GetTargetPositions_v5.obj 81680 \
//     build/survey/probes/w24c_GetTargetPositions_v5_fit.obj
extern int numVisibleTargets;            /* _numVisibleTargets */
extern unsigned short visibleTargetIds[];/* _visibleTargetIds */
extern void *objPtrs[];                  /* _objPtrs */
extern int __stdcall GRTo2d(int val, unsigned short *pos); /* _GRTo2d@8 */

void __fastcall GetTargetPositions_q(unsigned short *pos)
{
    int i = 0;
    unsigned short *pd, *pw;
    if (numVisibleTargets > 0) {
        pw = visibleTargetIds;
        pd = pos;
        do {
            if (GRTo2d((int)objPtrs[*pw] + 0x11, pd) < 0)
                *pd = 0x8000;
            pw++;
            pd += 2;
            i++;
        } while (numVisibleTargets > i);
    }
}