/* _toupper @ 0xd43d0 (869328), 110 B - CRT toupper wrapper: fast path
   (locale flag __ctype+0x388 clear) vs __lock/__toupper_lk slow path;
   __nstream+0x4/+0x8 = flag/hold-count pair. */
extern void __cdecl w33g_lock(int n);     /* -> __lock */
extern void __cdecl w33g_unlock(int n);   /* -> __unlock */
extern int  __cdecl w33g_tlk(int s);      /* -> __toupper_lk */
extern int  w33g_ctf;                     /* -> __ctype+0x388 */
extern int  w33g_s1;                      /* -> __nstream+0x4 */
extern int  w33g_s2;                      /* -> __nstream+0x8 */

int __cdecl w33g_toupper(int c)
{
    int flag, r;
    if (w33g_ctf == 0)
    {
        if (c >= 0x61 && c <= 0x7a)
            return c - 0x20;
        return c;
    }
    if (w33g_s1)
    {
        w33g_lock(0x13);
        flag = 1;
    }
    else
    {
        flag = 0;
        w33g_s2++;
    }
    r = w33g_tlk(c);
    if (flag)
    {
        w33g_unlock(0x13);
        return r;
    }
    w33g_s2--;
    return r;
}
