/* w42B 0x644a0 _CTEval_tgtaspectangle (160 B) v2 — v1 with t0/t1 decl order
 * swapped so the esp slots land t0@+0, t1@+2 (FA). */
extern unsigned short w26_svcGate;     /* map _w26_svcGate=_serviceTicks+0x20 */
extern unsigned int w26_svcTick;       /* map _w26_svcTick=_serviceTicks+0xf4 */
extern unsigned char w26_curThing11[]; /* map _w26_curThing11=_curThing+0x11 */
extern int __stdcall AnglesOffNoseQ(unsigned int t, void *thing, void *pr,
                                    void *z); /* _AnglesOffNoseQ@16=_AnglesOffNose@16 */
extern int __fastcall AbsQ(int v);     /* @AbsQ@4=@Abs@4 */

int CTEval_tgtaspectangle(void)
{
    short t1;
    short t0;
    short q;
    short m;

    if (w26_svcGate == 0)
        goto L0;
    AnglesOffNoseQ(w26_svcTick, (void *)w26_curThing11, &t1, &t0);
    t1 = AbsQ(*(int *)&t1);
    if (t1 > 0x3ffc)
        t1 = 0x7ff8 - t1;
    t0 = AbsQ(*(int *)&t0);
    if (t0 > 0x3ffc)
        t0 = 0x7ff8 - t0;
    m = t0 > t1 ? t0 : t1;
    q = 0xb6;
    return (int)(m / q);
L0:
    return 0;
}