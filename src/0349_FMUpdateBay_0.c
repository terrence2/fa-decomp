// _FMUpdateBay@0 @ rva 0x51d30 (335152 DEC; off 332080) (80 B) — EXACT
// winner (probe w24c_FMUpdateBay_v2.c). Pure CL C, NO patches.
//
// FA asm (0x42 body + census tail 8da42400000000 x2 = 14 B):
//   movsx eax,word ds:[_serviceTicks] / mov ecx,eax (s kept in ecx for the
//   strength-reduced multiply) / shl eax,14 / sub eax,ecx (s*16383) / cdq /
//   and edx,0xff / add eax,edx / sar eax,8 (signed /256) / mov cx,word
//   ds:[_curThing+0x23a] (arg1 headed, stale ecx uppers carry s) / push eax
//   (arg3 = delta, the one stack arg) / mov eax,ds:[_curThing+0x16f] /
//   and eax,0x200 / cmp eax,1 / sbb edx,edx / and dx,0x7fff (arg2 =
//   0x7fff if (flag&0x200)==0 else 0, computed in dx) / call
//   @TurnTowardAngle@12 / mov ds:[_curThing+0x23a],ax (result store) / ret.
//
// C recipe (the deltas that steered CL exactly):
//   - Read serviceTicks INLINE in the delta expression (no `int s` local):
//     with a local CL materializes the var in ecx first (movsx ecx) and the
//     copy comes out backwards (8bc1); inline the global read gives FA's
//     movsx eax + mov ecx,eax exactly.
//   - s*16383/256 signed in C emits shl 14/sub/cdq/and 255/add/sar 8.
//   - Interior reads via extern char array element expressions:
//     curThingQ[0x23a] (ushort) and curThingQ[0x16f] (ulong) — the addend
//     rides the array element, sites come out human-coin interior.
//   - Ternary (x&0x200) ? 0 : 0x7fff with the arg declared unsigned short:
//     CL emits and eax,0x200 / cmp 1 / sbb edx,edx / and dx,0x7fff.
//   - void __stdcall (cdecl would drop the @0); unsigned short fastcall
//     extern with 3 args (@...@12 = 4+4+4).
//
// Maps (obj FROM -> FA name): _curThingQ=_curThing (3 interior abs sites
// resolve as +0x23a/+0x16f), @TurnTowardAngle_q@12=@TurnTowardAngle@12.
// _serviceTicks is an identity anchor (declared extern short).
//
// Fit line:
//   python3 tools/fitobj.py build/survey/probes/w24c_FMUpdateBay_v2.obj 335152 \
//     build/survey/probes/w24c_FMUpdateBay_v2_fit.obj \
//     --map '_curThingQ=_curThing' --map '@TurnTowardAngle_q@12=@TurnTowardAngle@12'
extern char curThingQ[];   /* _curThing */
extern short serviceTicks; /* _serviceTicks */
extern unsigned short __fastcall TurnTowardAngle_q(unsigned short h, unsigned short d, unsigned long a3); /* @TurnTowardAngle@12 */

void __stdcall FMUpdateBay_q(void)
{
    *(unsigned short *)&curThingQ[0x23a] = TurnTowardAngle_q(
        *(unsigned short *)&curThingQ[0x23a],
        (unsigned short)((*(unsigned long *)&curThingQ[0x16f] & 0x200) ? 0 : 0x7fff),
        (unsigned long)(serviceTicks * 16383 / 256));
}
