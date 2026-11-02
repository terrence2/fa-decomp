/* w29g __forcdecpt @ 0xd9400 — v7: plain extern int guard (MB_CUR_MAX is a
 * bare int in the CRT — FA cmp [mem],edi), full-entry read + separate mask */
extern int w29g_mbmax;               /* -> __ctype+0x204 */
extern char w29g_decpt[];            /* -> __ctype+0x208 */
extern unsigned short *w29g_pct;     /* -> __pctype */
extern int __cdecl w29g_isctype(int c, int mask);   /* -> __isctype */
extern int __cdecl w29g_tolower(int c);             /* -> _tolower */

void __cdecl w29g_fdp(char *buf)
{
    char *p = buf;
    long d;
    char c, n, w;
    if (w29g_tolower(*p) != 'e') {
        do {
            p++;
            if (w29g_mbmax > 1)
                d = w29g_isctype(*p, 4);
            else
                d = w29g_pct[*p];
        } while (d & 4);
    }
    c = *p;
    *p = w29g_decpt[0];
    p++;
    for (;;) {
        n = *p;
        w = c;
        *p = w;
        c = n;
        p++;
        if (!w)
            break;
    }
}