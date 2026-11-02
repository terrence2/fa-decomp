/* ?PageText@@YIPADJ@Z @ 0x7c050 — v1: plain spelling */
extern long textNum;                 /* -> _textNum (identity) */
extern long *w28b_fmtP[];            /* -> _fmtText+0x10 */
extern void *w28b_fmtA[];            /* -> _fmtText */

char *__fastcall PageText_pg(long pg)
{
    long lim;
    char *list, *s;
    long i = textNum * 17;
    lim = w28b_fmtP[i];
    if (lim > pg) {
        list = (char *)w28b_fmtA[i];
        s = *(char **)(list + pg * 24 + 0x14);
        while (*s < 0x20)
            s++;
        return s;
    }
    return 0;
}
