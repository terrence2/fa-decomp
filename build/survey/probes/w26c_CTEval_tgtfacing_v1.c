// _CTEval_tgtfacing @ rva 0x64340 = 410432, 80 B (FA: sub esp,4; cmp WORD
// [_serviceTicks+0x20],0; jne L; xor eax,eax; add esp,4; ret // L: lea eax,
// [esp+2]; push 0; push eax; ecx=[_serviceTicks+0xf4]; push 0x508749
// (_curThing+0x11 push-addend); push ecx; call _AnglesOffNose@16;
// ecx,[esp+2] (dword read); call @Abs@4 fastcall; xor ecx,ecx;
// cmp eax,0x3ffc; setle cl; mov eax,ecx; add esp,4; ret).
// Local slot question: FA addresses the result WORD at [esp+2].
extern unsigned short w26_svcGate; /* map _w26_svcGate=_serviceTicks+0x20 */
extern unsigned int w26_svcTick; /* map _w26_svcTick=_serviceTicks+0xf4 */
extern unsigned char w26_curThing11[]; /* map _w26_curThing11=_curThing+0x11 */
extern int __stdcall AnglesOffNoseQ(unsigned int t, void *thing, void *pr, int z); /* map _AnglesOffNoseQ@16=_AnglesOffNose@16 */
extern int __fastcall AbsQ(int v); /* map @AbsQ@4=@Abs@4 */

int w26c_CTEval_tgtfacing_q(void)
{
    short r = 0;
    int b = 0;
    if (w26_svcGate) {
        AnglesOffNoseQ(w26_svcTick, (void *)w26_curThing11, &r, 0);
        b = AbsQ(*(int *)&r) <= 0x3ffc;
    }
    return b;
}