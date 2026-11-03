// 0xe2580 __chsize (104 B) — v1: w29f_close_v2 ioinfo spelling; fail path
// stores errno=9 only, NO doserrno store (FA bytes have none)
struct ioinfoX { long osfhnd; char osfile; };
extern unsigned long w32a_nhandle;         /* -> __nhandle */
extern char w32a_pio[];                    /* -> __crtheap+0x4 (__pioinfo) */
extern int __cdecl w32a_lkfh(int fh);      /* -> _lockfhandle_q */
extern long __cdecl w32a_chsizelk(int fh, long size); /* -> __chsize_lk */
extern int __cdecl w32a_unlockfh(int fh);  /* -> __unlock_fhandle */
extern long *__cdecl w32a_errno(void);     /* -> __errno */

long __cdecl w32a_chsize(int fh, long size)
{
    unsigned long o2;
    struct ioinfoX *e;
    if ((unsigned long)fh >= w32a_nhandle)
        goto fail;
    o2 = fh & 0x1f;
    o2 <<= 2;
    o2 += o2 * 8;
    e = (struct ioinfoX *)(*(unsigned long *)((char *)w32a_pio + ((fh & ~0x18) >> 3)) + o2);
    if (!(e->osfile & 1))
        goto fail;
    w32a_lkfh(fh);
    o2 = (unsigned long)w32a_chsizelk(fh, size);
    w32a_unlockfh(fh);
    return (long)o2;
fail:
    *w32a_errno() = 9;
    return -1;
}