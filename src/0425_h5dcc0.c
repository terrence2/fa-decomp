/* w43F 0x5dcc0 v2: drop the i=0 init (FA has none; slot passed by address
 * and read back); flip guard2 polarity: wingSizes[i] < 2 -> return 0, so
 * CL emits cmp cl,2 / jae (73) to the continuation with the zero-ret inline.
 */
extern char __stdcall w43F_WNGPP(long a, long *b, long c);
extern unsigned char w43F_wingSz[];     /* _wingSizes */
extern unsigned char w43F_wid2b[];      /* _wingIds+0x2 */

unsigned short __fastcall w43F_5dcc0(long a)
{
    unsigned long i;
    unsigned long t;
    if (w43F_WNGPP(a, (long *)&i, 0) != 1) return 0;
    if (w43F_wingSz[i] < 2) return 0;
    t = i * 4;
    return *(unsigned short *)(w43F_wid2b + t + t * 4);
}
