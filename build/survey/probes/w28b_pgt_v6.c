/* ?PageText@@YIPADJ@Z @ 0x7c050 — v6: no i local; inline 17x exprs (CSE order = statement order) */
extern long textNum;                 /* -> _textNum (identity) */
extern long *w28b_fmtP[];            /* -> _fmtText+0x10 */
extern void *w28b_fmtA[];            /* -> _fmtText */

char *__fastcall w28b_pgt_f6(long pg)
{
    long lim;
    char *s;
    lim = w28b_fmtP[textNum * 17];
    if (lim <= pg)
        return 0;
    s = *(char **)(*(char **)(w28b_fmtA + textNum * 17) + pg * 24 + 0x14);
    while (*(unsigned char *)s < 0x20)
        s++;
    return s;
}