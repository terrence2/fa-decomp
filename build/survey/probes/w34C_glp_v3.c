/* v3: FA widens w to a LONG copy (mov ax,cx leaves high dirty, cleared by the
 * 32-bit and eax,0x7fff / 32-bit cmp eax,0x7fff) — so spell the mask on a
 * long w2.  FA also has mov ebp,0x64 (mov ebp,0x64) inside the guard, before
 * the imul: assign dv = 100 just after the guard.  w declared before q (FA
 * keeps w in cx, q in bx). */
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
            w2 = w;
            dv = 100;
            if ((w2 & 0x7fff) != 0x7fff)
                *q = ((w2 & 0x7fff) * pct / dv) | (w & 0x8000);
        }
        i++;
    } while (w34c_tcnt > i);
}