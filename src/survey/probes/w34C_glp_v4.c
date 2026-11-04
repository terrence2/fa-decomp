/* v4: single widened statement — w2 = w & 0x7fff computed in LONG arithmetic
 * (FA: mov ax,cx + and eax,0x7fff / 32-bit cmp), dv local so mov ebp,0x64
 * lands before the imul. */
extern unsigned char w34c_tcnt;   /* =_curThingType+0xb5 */
extern unsigned char *__stdcall w34c_hp(unsigned long i, void **out,
                                        unsigned long z);
/* =_HARDPtrs@12 (stdcall, cleans 0xc) */

void __fastcall HARDGunLoadPercentW(long pct)
{
    void *p;
    unsigned short w;
    unsigned short *q;
    long w2;
    long dv;
    unsigned long t6;
    long i;

    i = 0;
    if (w34c_tcnt == 0)
        return;
    do {
        t6 = (unsigned long)w34c_hp(i, &p, 0);
        if (t6 != 0
            && *(unsigned char *)t6 == 7
            && *(unsigned long *)((char *)t6 + 0xa6) & 0x80) {
            q = (unsigned short *)p;
            w = q[2];
            q += 2;
            w2 = w & 0x7fff;
            dv = 100;
            if (w2 != 0x7fff)
                *q = (w2 * pct / dv) | (w & 0x8000);
        }
        i++;
    } while (w34c_tcnt > i);
}