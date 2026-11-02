/* w29g __forcdecpt @ 0xd9400 — v3: split q-local in the fast arm to steer
 * FA's char->ecx / table->edx plan */
extern char w29g_ct204[];            /* -> __ctype+0x204 */
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
            int q;
            p++;
            if (*(int *)w29g_ct204 > 1)
                d = w29g_isctype(*p, 4);
            else {
                q = *p;
                d = w29g_pct[q] & 4;
            }
        } while (d);
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