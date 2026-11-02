// 0xd81a0 __close — v2: struct-field osfile read (v8/v9 family spelling)
struct ioinfoX { long osfhnd; char osfile; };
extern unsigned long w29fNhandle;   /* -> __nhandle */
extern char w29fPio[];              /* -> __crtheap+0x4 (__pioinfo) */
extern int __cdecl w29fLockFH(int fh);
extern int __cdecl w29fCloseLk(int fh);
extern int __cdecl w29fUnlockFH(int fh);
extern long *__cdecl w29fErrno(void);
extern long *__cdecl w29fDosErrno(void);

int __cdecl closeX_q(int fh)
{
    unsigned long o2;
    struct ioinfoX *e;
    if ((unsigned long)fh >= w29fNhandle)
        goto fail;
    o2 = fh & 0x1f;
    o2 <<= 2;
    o2 += o2 * 8;
    e = (struct ioinfoX *)(*(unsigned long *)((char *)w29fPio + ((fh & ~0x18) >> 3)) + o2);
    if (!(e->osfile & 1))
        goto fail;
    w29fLockFH(fh);
    o2 = (unsigned long)w29fCloseLk(fh);
    w29fUnlockFH(fh);
    return (int)o2;
fail:
    *w29fErrno() = 9;
    *w29fDosErrno() = 0;
    return -1;
}