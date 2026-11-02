// _CTEval_tgtfacing @ rva 0x64340 = 410432, 80 B (no local init; gate
//   cmp [svc+0x20],0; jne body; xor eax; add esp,4; ret; body: lea eax,
//   [esp+2]; push 0; push eax; mov ecx,[svc+0xf4]; push &_curThing+0x11;
//   push ecx; call _AnglesOffNose@16; mov ecx,[esp+2]; call @Abs@4;
//   xor ecx; cmp eax,0x3ffc; setle cl; mov eax,ecx; add esp,4; ret.
//   v2: goto-spelling to force jne-to-body layout, no inits).
extern unsigned short w26_svcGate; /* map _w26_svcGate=_serviceTicks+0x20 */
extern unsigned int w26_svcTick; /* map _w26_svcTick=_serviceTicks+0xf4 */
extern unsigned char w26_curThing11[]; /* map _w26_curThing11=_curThing+0x11 */
extern int __stdcall AnglesOffNoseQ(unsigned int t, void *thing, void *pr, int z); /* map _AnglesOffNoseQ@16=_AnglesOffNose@16 */
extern int __fastcall AbsQ(int v); /* map @AbsQ@4=@Abs@4 */

int w26c_CTEval_tgtfacing_q(void)
{
    short r;
    int b;
    if (w26_svcGate == 0)
        goto L0;
    AnglesOffNoseQ(w26_svcTick, (void *)w26_curThing11, &r, 0);
    b = AbsQ(*(int *)&r) <= 0x3ffc;
    return b;
L0:
    return 0;
}