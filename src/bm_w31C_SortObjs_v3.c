/* wave 31C: @SortObjs@8 (FA rva 0x120d0, 0x90 B) v3 - partition as inner for(;;) */
typedef int *PI;

void __fastcall w31cSo(PI *lo, PI *hi)
{
    PI *i, *j, t;
    i = lo;
    j = hi + 1;
    if (hi <= lo) return;
    do {
        for (;;) {
            do {
                ++i;
            } while (i < hi && **i >= **lo);
            do {
                --j;
            } while (lo < j && **j <= **lo);
            if (i < j) {
                t = *i;
                *i = *j;
                *j = t;
                continue;
            }
            break;
        }
        t = *lo;
        *lo = *j;
        *j = t;
        if ((long)(hi - j) <= (long)(j - lo)) {
            w31cSo(j + 1, hi);
            hi = j - 1;
            i = lo;
        } else {
            w31cSo(lo, j - 1);
            lo = j + 1;
            i = lo;
            j = hi + 1;
        }
    } while (hi > lo);
}