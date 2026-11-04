/* __close_lk v1: plain C. Map _w37a_fhl=__crtheap+0x4 (interior ioinfo ptr
 * table); row/idx staging per n1_Isatty recipe. */
extern unsigned long __cdecl _get_osfhandle(int);
extern void __cdecl _free_osfhnd(int);
extern void __cdecl _dosmaperr(long);
__declspec(dllimport) int __stdcall CloseHandle(unsigned long);
__declspec(dllimport) unsigned long __stdcall GetLastError(void);
extern char _w37a_fhl[];

int _close_lk(int fh)
{
    unsigned char *row;
    int e, idx, grp;
    if ((fh == 1 || fh == 2)
            && (unsigned long)_get_osfhandle(2) == (unsigned long)_get_osfhandle(1))
        goto done;
    if (CloseHandle(_get_osfhandle(fh)))
        goto done;
    e = GetLastError();
    goto end;
done:
    e = 0;
end:
    _free_osfhnd(fh);
    if (e != 0) {
        _dosmaperr(e);
        return -1;
    }
    grp = (fh & ~0x18) >> 3;
    idx = (fh & 0x1f) << 2;
    row = *(unsigned char **)((char *)_w37a_fhl + grp);
    row[idx + 4] = 0;
    return 0;
}