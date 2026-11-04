/* __commit (162 B) - CRT _commit(long fd): validate handle, resolve the
   pioinfo cell, re-verify the FOPEN byte across _lock_fhandle, flush, then
   doserrno/errno on failure. FA = ebx:cell-table pointer, edi:cell offset
   then err. Goto-joined BADFD/errno epilogues duplicated per exit. */
extern unsigned long w43c_nh;                    /* __nhandle @ 0x588d70 */
extern char w43c_piob[];                         /* __crtheap+0x4 */
extern void __cdecl w43c_lkf(long fd);           /* __lock_fhandle */
extern unsigned long __cdecl w43c_osfh(long fd); /* __get_osfhandle */
extern void __cdecl w43c_ulf(long fd);           /* __unlock_fhandle */
extern unsigned long __stdcall w43c_ffb(unsigned long h);  /* FlushFileBuffers */
extern unsigned long __stdcall w43c_gle(void);   /* GetLastError */
extern long *w43c_errq(void);                    /* __errno */
extern long *w43c_gpq(void);                     /* $FA$_t_4d99c0 */
long w43c_commit(long fd)
{
    long *p, err;
    long cell;
    if ((unsigned long)fd >= w43c_nh)
        goto BAD;
    p = (long *)(w43c_piob + ((fd & ~24) >> 3));
    cell = (fd & 31) * 36;
    if (!(*(char *)((char *)*p + cell + 4) & 1))
        goto BAD;
    w43c_lkf(fd);
    err = 0;
    if (!(*(char *)((char *)*p + cell + 4) & 1))
        goto D2;
    if (!w43c_ffb(w43c_osfh(fd)))
        err = w43c_gle();
    if (err) {
        *(long *)w43c_gpq() = err;
D2:     err = -1;
    }
    if (err)
        *w43c_errq() = 9;
    w43c_ulf(fd);
    return err;
BAD:
    *w43c_errq() = 9;
    return -1;
}
