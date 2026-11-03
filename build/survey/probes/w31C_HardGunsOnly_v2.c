/* wave 31C: _HARDGunsOnly@0 (FA rva 0x529f0, 0x70 B) v2 - no return-assign on out-arg call */
extern long __stdcall w31cFS(long *, long, long);    /* _HARDFindStore@12 */
extern void *__stdcall w31cHP(long, void **, long);  /* _HARDPtrs@12 */
extern void __fastcall w31cUn(long, long);           /* @HARDUnload@8 */

void __stdcall w31cGO(void)
{
    long loc;
    void *pv;
    long idx;
    unsigned long mask;
    loc = 0x7fffffff;
    mask = 0x80;
    do {
        idx = w31cFS(&loc, 7, 255);
        if (idx == -1) break;
        pv = w31cHP(idx, 0, 0);
        if (pv == 0) continue;
        if (*(unsigned long *)((char *)pv + 0xa6) & mask) continue;
        w31cUn(idx, 0);
        w31cHP(idx, &pv, 0);
        *(long *)pv = 0;
    } while (1);
}