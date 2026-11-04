/* w37B 0x73690 (rva 472720, 128 B) @AmmoForClass@4 v2: fastcall(mask=ecx).
 * v1 differed only in the rec register plan: FA keeps the HARDFindStore
 * result AND the HARDPtrs RETURN in EAX (the C reassigns p = HARDPtrs(...)),
 * so no ebx spill / no [esp+0xc] shift. Loop: need = 0x10000 if mask&0xc000,
 * |= 0x20000 if mask&0x3fff; v = 0x7fffffff; for(;;) HARDFindStore(&v,7,0xff);
 * rec==-1 -> ret0; HARDPtrs(rec,&a,&b)==0 -> retry; a->word+4<=0 -> retry;
 * b->byte0 & 2 -> retry; need & [rec+0xa6] -> ret1 (need live in esi). */
extern void *__stdcall HARDFindStore(void *v, long a, long b);   /* _HARDFindStore@12 */
extern void *__stdcall HARDPtrs(void *rec, void **a, void **b);  /* _HARDPtrs@12 */

char __fastcall AmmoForClass(long mask)
{
    long v;
    void *a;
    void *b;
    long need = 0;
    void *p;

    if (mask & 0xc000)
        need = 0x10000;
    if (mask & 0x3fff)
        need |= 0x20000;
    v = 0x7fffffff;
    for (;;) {
        p = HARDFindStore(&v, 7, 0xff);
        if (p == (void *)-1)
            return 0;
        p = HARDPtrs(p, &a, &b);
        if (p == 0)
            continue;
        if (*(short *)((char *)a + 4) <= 0)
            continue;
        if (*(char *)b & 2)
            continue;
        if (need & *(long *)((char *)p + 0xa6))
            return 1;
    }
}