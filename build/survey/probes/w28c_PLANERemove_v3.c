// 0x9b540 — v3: p and i as separate vars (FA: p=edx, i=edi(long), npl=si,
// c=ebx, nxt=lea'd eax); found-pointer recomputed from i
extern short w28c_numPlanesT;
extern short w28c_planesArr[];

void __fastcall w28c_PLANERemove(short idx)
{
    short npl, t;
    long i, c;
    short *p, *nxt;

    npl = w28c_numPlanesT;
    i = 0;
    if (npl > 0) {
        p = w28c_planesArr;
        for (;;) {
            if (*p == idx) goto found;
            p++;
            i++;
            if (i >= (long)npl) return;
        }
found:
        if (i < (long)npl - 1) {
            c = (long)npl - i - 1;
            p = (short *)w28c_planesArr + i;
            do {
                t = p[1];
                nxt = p + 1;
                *p = t;
                p = nxt;
            } while (--c != 0);
        }
    }
    npl--;
    w28c_numPlanesT = npl;
}
