/* ?PageText@@YIPADJ@Z @ 0x7c050 — v4: pp bare decl, assigned after lim */
extern long textNum;                 /* -> _textNum (identity) */
extern long *w28b_fmtP[];            /* -> _fmtText+0x10 */
extern void *w28b_fmtA[];            /* -> _fmtText */

char *__fastcall w28b_pgt_f4(long pg)
{
    long lim;
    char *list, *s;
    char **pp;
    long i = textNum * 17;
    lim = w28b_fmtP[i];
    pp = (char **)w28b_fmtA + i;
    if (lim <= pg)
        return 0;
    list = *pp;
    s = *(char **)(list + pg * 24 + 0x14);
    while (*(unsigned char *)s < 0x20)
        s++;
    return s;
}