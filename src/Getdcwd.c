// __getdcwd @ rva 0xd52a0 (50 B) — char *_getdcwd(int drive, char *buf,
// unsigned maxlen): _LOCK_NUMBER for drive = 12 (_LOCK_DRIVE), the three
// args loaded into eax/ecx/edx (arg3 first) BEFORE the add esp,4 lock-arg
// pop, then pushed right-to-left into __getdcwd_lk; result held in esi
// across _unlock(12), returned. Plain right-to-left C (Getcwd sibling
// precedent, wave-13 w13c_gcwd1 exact).
extern void __cdecl _lock(int n);
extern char *__cdecl _getdcwd_lk(int drive, char *buf, unsigned maxlen);
extern void __cdecl _unlock(int n);

char * __cdecl _getdcwd(int drive, char *buf, unsigned maxlen)
{
    char *r;
    _lock(12);
    r = _getdcwd_lk(drive, buf, maxlen);
    _unlock(12);
    return r;
}