/* __read v1: plain C, ioinfo table guard + lock/read_lk/unlock. */
extern void __cdecl _lock_fhandle(int);
extern void __cdecl _unlock_fhandle(int);
extern int __cdecl _read_lk(int, void *, unsigned int);
extern int *__cdecl _errno(void);
extern int *__cdecl _w37a_doserrno(void);    /* = $FA$_t_4d99c0 */
extern unsigned int _nhandle;
extern char _w37a_fhl[];

int _read(int fh, void *buf, unsigned int cnt)
{
    unsigned char *row;
    int ret, idx, grp;
    if ((unsigned int)fh >= _nhandle)
        goto bad;
    grp = (fh & ~0x18) >> 3;
    idx = (fh & 0x1f) << 2;
    row = *(unsigned char **)((char *)_w37a_fhl + grp);
    if (!(row[idx + 4] & 1))
        goto bad;
    _lock_fhandle(fh);
    ret = _read_lk(fh, buf, cnt);
    _unlock_fhandle(fh);
    return ret;
bad:
    *_errno() = 9;
    *_w37a_doserrno() = 0;
    return -1;
}