// 0x9b540 — v2: FA reg plan npl=si (cached short), i=edi (long), c=ebx
extern short w28c_numPlanesT;
extern short w28c_planesArr[];

void __fastcall w28c_PLANERemove(short idx)
{
    short npl, t;
    long i, c;

    npl = w28c_numPlanesT;
    i = 0;
    if (npl > 0) {
        for (;;) {
            if (w28c_planesArr[i] == idx) break;
            i++;
            if (i >= (long)npl) return;
        }
        if (i < (long)npl - 1) {
            c = (long)npl - i - 1;
            do {
                t = w28c_planesArr[i + 1];
                w28c_planesArr[i] = t;
                c--;
            } while (c != 0);
        }
        npl--;
        w28c_numPlanesT = npl;
    }
}
