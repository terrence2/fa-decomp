// _CTEval_ptotgt @ rva 0x64450 = 410704, 80 B (twin: arg3=0, arg4=&local;
//   FA: lea eax,[esp+2]; push eax; push 0; mov eax,[svc+0xf4];
//   add eax,0x11; push eax; push &_curThing+0x11; call _Angles@16; same
//   idiv tail. v2: goto gate spelling).
extern unsigned short w26_svcGate; /* map _w26_svcGate=_serviceTicks+0x20 */
extern unsigned int w26_svcTick; /* map _w26_svcTick=_serviceTicks+0xf4 */
extern unsigned char w26_curThing11[]; /* map _w26_curThing11=_curThing+0x11 */
extern int __stdcall AnglesQ(unsigned int thing, unsigned int t, void *pr, int z); /* map _AnglesQ@16=_Angles@16 */

int w26c_CTEval_ptotgt_q(void)
{
    short r;
    short q;
    if (w26_svcGate == 0)
        goto L0;
    AnglesQ((unsigned int)w26_curThing11, w26_svcTick + 0x11, 0, &r);
    q = r / 0xb6;
    return (int)q;
L0:
    return 0;
}