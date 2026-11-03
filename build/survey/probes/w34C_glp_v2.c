/* v2: FA does xor edi,edi (i=0) BEFORE the tcnt test, no nop; w is 16-bit
 * (FA keeps w in cx: 66 8b 4b 04 / mov ax,cx); q is the saved pointer reg
 * (ebx). */
extern unsigned char w34c_tcnt;   /* =_curThingType+0xb5 */
extern unsigned char *__stdcall w34c_hp(unsigned long i, void **out,
                                        unsigned long z);
/* =_HARDPtrs@12 (stdcall, cleans 0xc) */

void __fastcall HARDGunLoadPercentW(long pct)
{
    void *p;
    unsigned short *q;
    unsigned short w;
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
            if ((w & 0x7fff) != 0x7fff)
                *q = ((w & 0x7fff) * pct / 100)
                   | (w & 0x8000);
        }
        i++;
    } while (w34c_tcnt > i);
}