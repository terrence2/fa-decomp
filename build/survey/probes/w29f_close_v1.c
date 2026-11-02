// 0xd81a0 __close — v1 (CRT CLOSE.C shape per get_osfhandle idiom)
struct ioinfoX { long osfhnd; char osfile; char pipech[5]; };
extern unsigned long w29fNhandle;   /* -> __nhandle */
extern char w29fPio[];              /* -> __crtheap+0x4 (__pioinfo) */
extern int __cdecl w29fLockFH(int fh);
extern int __cdecl w29fCloseLk(int fh);
extern int __cdecl w29fUnlockFH(int fh);
extern long *__cdecl w29fErrno(void);
extern long *__cdecl w29fDosErrno(void);

int __cdecl closeX_q(int fh)
{
    long r, o2;
    if ((unsigned long)fh >= w29fNhandle)
        goto fail;
    o2 = fh & 0x1f;
    o2 <<= 2;
    o2 += o2 * 8;
    if (!(*(unsigned char *)(*(unsigned long *)((char *)w29fPio + ((fh & ~0x18) >> 3)) + o2 + 4) & 1))
        goto fail;
    w29fLockFH(fh);
    r = w29fCloseLk(fh);
    w29fUnlockFH(fh);
    return (int)r;
fail:
    *w29fErrno() = 9;
    *w29fDosErrno() = 0;
    return -1;
}