/* w46F:v3 FA rva 339040 _HARDUnlimited@0 (208 B).
 * v3 = v2 with else-chaining (FA negates the rec/*L1 tests and jumps to
 * the increment+test tail, so no continue skipping the i++) and the w==0
 * default reload back on L2 (FA reads [esp+0x14] after the stdcall-cleanup
 * HARDCanLoad: slot B, not slot A). */
extern unsigned char _curThing[];
extern unsigned char _curThingType[];

#define CT_DE  (*(int *)(_curThing + 0xde))
#define CTT_B5 (*(volatile unsigned char *)(_curThingType + 0xb5))

extern unsigned char *__stdcall HARDPtrs(int, int **, int **);
extern int __fastcall NextString(int, int);
extern int __stdcall HARDCanLoad(int, int);
extern void __stdcall HARDLoad(int, int, int);

void __stdcall HARDUnlimited(void)
{
    int *L1, *L2, w, lim, i, s;
    unsigned char *rec;

    i = 0;
    if (CTT_B5 == 0)
        return;
    lim = 0x8000;
    for (;;) {
        rec = HARDPtrs(i, &L1, &L2);
        if (rec != 0) {
            if (*L1 != 0) {
                if (*rec == 7) {
                    s = NextString(*(int *)(rec + 5), 2);
                    w = HARDCanLoad(i, s);
                    if (w == 0)
                        w = *(short *)((char *)L2 + 0x15);
                    if (lim & CT_DE)
                        w = *(short *)(rec + 0xaa) * w;
                    HARDLoad(i, s, w);
                } else if (*rec == 9) {
                    int v = *(unsigned short *)((char *)L1 + 4) & 0x7fff;
                    *(char *)((char *)L1 + 6) = *(signed char *)(rec + 0xa) * v;
                    *(char *)((char *)L1 + 7) = *(signed char *)(rec + 0xe) * v;
                }
            }
        }
        i++;
        if ((int)CTT_B5 <= i)
            break;
    }
}