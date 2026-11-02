// _CTEval_maxalt @ rva 411424 (0x64720, 48 B) — patch-hybrid.  Large-span
//   note: the patch replaces the full 47-byte tail from offset 1 — FA:
//   push esi; push 0 (arg slot); 66 a1 word-load of curId into eax parked
//   OUTSIDE the push interleave; 8b 35 esi-load of curThingType+0x79 (the
//   maxalt value, kept live across the call); remaining pushes 6a 00 6a 00
//   then the two pointer args curThing+0x11 and curThing and finally the
//   parked curId (50); call T_Info; tail sub esi,eax / sar esi,8 / mov
//   eax,esi / pop esi / ret + 8d 64 24 00 pad.  CL hoists its pushed-arg
//   pre-computation INTO the push block (lea eax,(curThing+0x11) up front,
//   three bare 6a 00 pushes, 68 zero high-arg, xor eax + 66 a1 word-load
//   interleaved between pushes) — the documented CTEval_alt push-interleave
//   hoist wall (twin alt twin probes failed the same way), so the tail is
//   FA-synthesized with abs sites retargeted to fresh symbols.
//   Probe build/survey/probes/p_w23_CTEval_maxalt_patch.obj EXACT
//   (w23_r5.json; ladder w23_CTEval_maxalt_v1/v2 + alt twin probes).
//   Maps (swap.json verbatim + patch sites):
//     cTT79=_curThingType+0x79, cThing11=_curThing+0x11.
//   Patch: "1,47,6a0066a1242f4f008b35998b50006a006a006849875000683887500050e82d4204002bf0c1fe088bc65ec38d642400,4:6:_curId,10:6:cTT79,19:6:cThing11,24:6:_curThing,30:20:_T_Info@24".
extern unsigned short curId;
extern char curThing[];
extern char curThingType[];
extern long __stdcall T_Info(long a, long b, long c, long d, long e, long f);

long CTEval_maxalt_q(void)
{
    long wt = *(long *)((char *)curThingType + 0x79);
    long ti = T_Info(curId, (long)curThing, (long)curThing + 0x11, 0, 0, 0);
    return (wt - ti) >> 8;
}