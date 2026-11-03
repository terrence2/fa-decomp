/* wave 31C: @HARDFindJammer@4 (FA rva 0x524c0, 0x70 B) v2 - separate scratch slot */
extern long __stdcall w31cFS(long *, long, long);    /* _HARDFindStore@12 */
extern void *__stdcall w31cHP(long, void **, long);  /* _HARDPtrs@12 */

long __fastcall w31cFJ(unsigned char kind)
{
    long loc;
    long scratch;
    void *pv;
    long idx;
    unsigned short w2;
    loc = 0x7fffffff;
    do {
        idx = w31cFS(&loc, 9, 255);
        if (idx == -1) return -1;
        pv = w31cHP(idx, &scratch, 0);
        if (pv == 0) continue;
        w2 = *(unsigned short *)((char *)pv + 8);
        if ((kind == 2 && (w2 & 0x100)) || (kind == 3 && (w2 & 0x10)))
            return idx;
    } while (1);
}