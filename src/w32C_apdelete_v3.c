/* w32C apdelete v3: v2 C with the rotation loop spelled as memcpy(dst,
 * dst+1, 308) so CL inlines it to mov ecx,0x4d / rep movsd like FA's
 * edi/esi loop (rep leaves flags from the preceding dec edx, whose ZF the
 * outer jne tests). Slot stride 0x134 = 77 longs + 1 next-slot ref. */
typedef unsigned long W32CSLOT[77];

extern short numAirports;   /* _numAirports identity */
extern long airports[];     /* _airports identity */
extern void *memcpy(void *, const void *, unsigned long);

void __fastcall w32cApDeleteF3(unsigned short slotId)
{
    W32CSLOT *pp, *dst;
    short n;
    long w, i, i9, i19, i77;

    n = numAirports;
    i = 0;
    if (n <= (short)i) {
        return;
    }
    pp = (W32CSLOT *)((char *)airports + 0xe6);
    for (;;) {
        if (*(unsigned short *)pp == slotId) {
            break;
        }
        pp = (W32CSLOT *)((char *)pp + 0x134);
        i = i + 1;
        w = n;
        if (i < w) {
            continue;
        }
        return;
    }
    w = n;
    if (i >= w - 1) {
        goto dec;
    }
    i9 = i + i * 8;
    w = w - i;
    w = w - 1;
    i19 = i + i9 * 2;
    i77 = i + i19 * 4;
    dst = (W32CSLOT *)(airports + i77);
    for (;;) {
        w = w - 1;
        memcpy(dst, dst + 1, 308);
        dst = (W32CSLOT *)((char *)dst + 0x134);
        if (w == 0) {
            break;
        }
    }
dec:
    n = n - 1;
    numAirports = n;
    return;
}