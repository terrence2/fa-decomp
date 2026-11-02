// _HARDLoadAll@0 @ rva 0x52330 (80 B) — probe v1.
extern char curThingTypeQ[];  /* _curThingType */
extern void __stdcall HARDPtrs_q(long t, unsigned long z, void **out); /* _HARDPtrs@12 */
extern void __stdcall HARDLoad_q(long t, unsigned long a, unsigned long b); /* _HARDLoad@12 */

void __stdcall HARDLoadAll_q(void)
{
    void *p;
    long i = 0;
    if (curThingTypeQ[0xb5]) {
        do {
            unsigned long ld;
            HARDPtrs_q(i, 0, &p);
            ld = *(unsigned long *)((char *)p + 0x10);
            if (ld)
                HARDLoad_q(i, ld, 0);
            i++;
        } while (curThingTypeQ[0xb5] > i);
    }
}
