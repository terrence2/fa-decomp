/* wave 31C: @HARDUnload@8 (FA rva 0x51e10, 0x80 B) v1 */
extern void __stdcall w31cHP(long, void **, long);   /* _HARDPtrs@12 */
extern void __stdcall w31cSF(void);                  /* _HARDSetFlags@0 */

unsigned char __fastcall w31cUn(long a, long b)
{
    void *pv;
    unsigned short w;
    unsigned long lim;
    unsigned char r;
    w31cHP(a, &pv, 0);
    if (pv == 0) return 0;
    w = *(unsigned short *)((char *)pv + 4);
    lim = w & 0x7fff;
    if (b == 0) {
        lim = 0;
        r = 1;
    } else if (lim == 0x7fff) {
        r = 1;
    } else if ((long)lim < 1) {
        r = 0;
    } else {
        lim -= b;
        if ((long)lim < 0) lim = 0;
        r = 1;
    }
    *(unsigned short *)((char *)pv + 4) = (unsigned short)((w & 0x8000) | lim);
    w31cSF();
    return r;
}