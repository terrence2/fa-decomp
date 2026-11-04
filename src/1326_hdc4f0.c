/* w38G __lseek_lk @ 0xdc4f0 (130 B, FPO 2-reg) — v1 plain C.
 * imp calls: SetFilePointer/GetLastError via dllimport stdcall decls (CL
 * emits __imp__X@N; parent maps to FA's undecorated __imp__X names). */
extern unsigned long w38g_lsp;                /* -> __crtheap+0x4 */
extern int *__cdecl w38g_errnoX(void);        /* -> __errno */
extern void __cdecl w38g_dme(long);           /* -> __dosmaperr */
extern unsigned long __cdecl _get_osfhandle(int);

__declspec(dllimport) unsigned long __stdcall SetFilePointer(unsigned long, long, void *, int);
__declspec(dllimport) unsigned long __stdcall GetLastError(void);

long __cdecl w38g_lsl(int fh, long pos, int org)
{
    unsigned long h, err;
    char *row;
    unsigned long o2;

    h = _get_osfhandle(fh);
    if (h == 0xffffffff) {
        *w38g_errnoX() = 9;
        return -1;
    }
    h = SetFilePointer(h, pos, 0, org);
    err = 0;
    if (h == 0xffffffff)
        err = GetLastError();
    if (err != 0) {
        w38g_dme(err);
        return -1;
    }
    o2 = (unsigned long)(fh & 0x1f);
    o2 <<= 2;
    o2 = o2 + o2 * 8;
    row = *(char **)((char *)&w38g_lsp + ((fh & ~0x18) >> 3));
    row[o2 + 4] &= 0xfd;
    return (long)h;
}