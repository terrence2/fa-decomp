// __getcwd @ rva 0xd5270 (47 B) — char * _getcwd(char *path, unsigned
// maxlen): grab the 0xc (=12, _CWD_LOCK) lock, _getdcwd_lk(0, path, maxlen)
// under it, drop the lock, return. Note FA's arg loads both happen BEFORE
// the add esp,4 cleanup (mov eax,[esp+0x10] maxlen, mov ecx,[esp+0xc]
// path), then push eax/push ecx/push 0 — plain right-to-left C gives this
// interleaving (probe w13c_gcwd1 exact, byte-for-byte).
extern void __cdecl _lock(int n);
extern char *__cdecl _getdcwd_lk(int drive, char *path, unsigned len);
extern void __cdecl _unlock(int n);

char *__cdecl _getcwd(char *path, unsigned maxlen)
{
    char *r;
    _lock(12);
    r = _getdcwd_lk(0, path, maxlen);
    _unlock(12);
    return r;
}