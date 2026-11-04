/* w43F 0x2fc80 v2 (do-while): fastcall long key in ecx; two pointer-walk
 * searches over address-literal spans (_specials+0xe10..+0xe24 and
 * +0xf48..+0xf5c); hit returns i (eax), exhaust returns 0.  Bound compares
 * are folded imms (81 fa); pointer walker edx, counter eax, temp ebx.
 * FA end layout: exhaust-ret 33 c0 5b c3 then pad + 5b c3 hits (4 inserts).
 */
extern unsigned long w43F_spA[];
extern unsigned long w43F_spAe[];
extern unsigned long w43F_spB[];
extern unsigned long w43F_spBe[];

long __fastcall w43F_2fc80(long key)
{
    unsigned long *p, i;
    i = 0;
    p = w43F_spA;
    do {
        if (*p == (unsigned long)key) return (long)i;
        p++;
        i++;
    } while (p < w43F_spAe);
    i = 0;
    p = w43F_spB;
    do {
        if (*p == (unsigned long)key) return (long)i;
        p++;
        i++;
    } while (p < w43F_spBe);
    return 0;
}
