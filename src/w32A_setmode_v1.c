// 0xe4620 __setmode (104 B) — v1: chsize twin; FA compare is mem-form
// cmp [nhandle],esi + jbe (try nhandle<=fh spelling); lk target is the
// CONVERTED _w29g_smlk
struct ioinfoX { long osfhnd; char osfile; };
extern unsigned long w32b_nhandle;         /* -> __nhandle */
extern char w32b_pio[];                    /* -> __crtheap+0x4 (__pioinfo) */
extern int __cdecl w32b_lkfh(int fh);      /* -> _lockfhandle_q */
extern int __cdecl w32b_setmodelk(int fh, int mode);  /* -> _w29g_smlk */
extern int __cdecl w32b_unlockfh(int fh);  /* -> __unlock_fhandle */
extern long *__cdecl w32b_errno(void);     /* -> __errno */

int __cdecl w32b_setmode(int fh, int mode)
{
    unsigned long o2;
    struct ioinfoX *e;
    if ((unsigned long)w32b_nhandle <= (unsigned long)fh)
        goto fail;
    o2 = fh & 0x1f;
    o2 <<= 2;
    o2 += o2 * 8;
    e = (struct ioinfoX *)(*(unsigned long *)((char *)w32b_pio + ((fh & ~0x18) >> 3)) + o2);
    if (!(e->osfile & 1))
        goto fail;
    w32b_lkfh(fh);
    o2 = (unsigned long)w32b_setmodelk(fh, mode);
    w32b_unlockfh(fh);
    return (int)o2;
fail:
    *w32b_errno() = 9;
    return -1;
}