// 0x9b540 @PLANERemove@4 @ 0x49b540 — v4: dec+store in the found path only
// (FA: entry jle skips to the shared pops, not-found exits early; do-while
// scan so CL keeps npl in si across the loop)
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
        do {
            if (*p == idx) goto found;
            p++;
            i++;
        } while (i < (long)npl);
        return;
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
        npl--;
        w28c_numPlanesT = npl;
    }
}