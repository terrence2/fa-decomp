// 0x9b540 @PLANERemove@4 (96 B) — v1
extern short w28c_numPlanesT;   /* _numPlanes (word) */
extern short w28c_planesArr[];  /* _planes (word array) */

void __fastcall w28c_PLANERemove(short idx)
{
    short i, n, npl;

    npl = w28c_numPlanesT;
    i = 0;
    while (i < npl) {
        if (w28c_planesArr[i] == idx) break;
        i++;
    }
    if (i == npl) return;
    if (i < npl - 1) {
        char *p;
        n = npl - i - 1;
        p = (char *)&w28c_planesArr[i];
        do {
            *(short *)p = *(short *)(p + 2);
            p += 2;
        } while (--n);
    }
    w28c_numPlanesT = npl - 1;
}
