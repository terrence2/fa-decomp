/* 0x1f2e0 (unnamed, 64 B): thiscall(fastcall-with-ecx) char append from
 * *(char **)namePtr until pred pair (h1/h2, h2 in ecx) returns nonzero.
 * FA: guard call OUTSIDE the do-while (latch re-enters at copy head). */
extern void w38a_set(void);       /* $FA$_t_41f340 */
extern int  w38a_h1(void);        /* $FA$_t_41f280 */
extern char __fastcall w38a_h2(int);  /* $FA$_t_41f320, ecX=h1's eax */
extern char *w38a_namePtr;        /* ?janesOnlineName@@3PADA+0xb8 */

void __fastcall w38a_1f2e0(char *dst)
{
    char *d = dst;
    w38a_set();
    if (w38a_h2(w38a_h1())) {
        *d = 0;
        return;
    }
    do {
        *d++ = *w38a_namePtr;
        ++w38a_namePtr;
    } while (!w38a_h2(w38a_h1()));
    *d = 0;
}