/* @HARDGunLoadPercent@4 @ rva 0x52ab0 (338608, 128 B) — fastcall void(long pct):
 * thingCount (byte @ _curThingType+0xb5) loop i<count; HARDPtrs(i,&p,0); if
 * (ret && *(unsigned char*)ret==7 && DWORD ret[0xa6]&0x80) { w = q[2] (word at
 * p+4); q += 2; if ((w&0x7fff)!=0x7fff)
 * *q = ((w&0x7fff)*pct/100) | (w&0x8000); } */
extern unsigned char w34c_tcnt;   /* =_curThingType+0xb5 */
extern unsigned char *__stdcall w34c_hp(unsigned long i, void **out,
                                        unsigned long z);
/* =_HARDPtrs@12 (stdcall, cleans 0xc) */

void __fastcall HARDGunLoadPercentW(long pct)
{
    void *p;
    unsigned short *q;
    unsigned long w, t6;
    long i;

    if (w34c_tcnt == 0)
        return;
    i = 0;
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