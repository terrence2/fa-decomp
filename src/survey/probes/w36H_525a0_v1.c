/* _HARDFindStore@12 @ rva 0x525a0 (112 B) -- v1 plain C.
 * stdcall (long *store, unsigned char k1, unsigned char k2): clamp
 * *store to the curThingType+0xb5 byte (u8-widened), then scan down with
 * HARDPtrs(i, &outp, zero); hit when *ret == k1 or k2; -1 path re-stores
 * -1 after pop edi. */
extern char curThingType[];
extern void *__stdcall HARDPtrs(long idx, void **outp, long zero);

long __stdcall HARDFindStore(long *store, unsigned char k1, unsigned char k2)
{
    unsigned long cap;
    long i, zero = 0;
    void *outp, *rp;
    unsigned char b;

    cap = (unsigned long)(unsigned char)*((unsigned char *)curThingType + 0xb5);
    if (*store >= (long)cap)
        *store = cap;
    for (;;) {
        i = *store - 1;
        *store = i;
        if (i < 0) {
            *store = -1;
            return -1;
        }
        rp = HARDPtrs(i, &outp, zero);
        if (*(short *)((char *)outp + 4) <= zero)
            continue;
        if (rp == 0)
            continue;
        b = *(unsigned char *)rp;
        if (b == k1)
            break;
        if (k2 != b)
            continue;
        break;
    }
    return *store;
}