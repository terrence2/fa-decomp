/* w29g __forcdecpt @ 0xd9400 — v8: ternary-macro shape in the while
 * condition (isdigit macro spelling); plain extern int guard */
extern int w29g_mbmax;               /* -> __ctype+0x204 */
extern char w29g_decpt[];            /* -> __ctype+0x208 */
extern unsigned short *w29g_pct;     /* -> __pctype */
extern int __cdecl w29g_isctype(int c, int mask);   /* -> __isctype */
extern int __cdecl w29g_tolower(int c);             /* -> _tolower */

void __cdecl w29g_fdp(char *buf)
{
    char *p = buf;
    char c, n, w;
    if (w29g_tolower(*p) != 'e') {
        do {
            p++;
        } while (w29g_mbmax > 1 ? w29g_isctype(*p, 4) : (w29g_pct[*p] & 4));
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