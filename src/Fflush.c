// _fflush @ rva 0xd5eb0 (57 B) — int _fflush(FILE *f): NULL stream =>
// _allflush(0) (the flush-all helper parked at $FA$_t_4d5fb0, called with a
// 0 flag and NOT tail-called: push 0 / call / add esp,4); otherwise lock the
// FILE, __fflush_lk, unlock. Result rides edx->edi (r in edi, f in esi;
// probe w13c_fflush1 first emitted a 0-arg flushall call — the helper takes
// the flag arg, w13c_fflush2 exact).
extern int __cdecl _allflush(int flag);
extern void __cdecl _lock_file(void *f);
extern int __cdecl _fflush_lk(void *f);
extern void __cdecl _unlock_file(void *f);

int __cdecl _fflush(void *f)
{
    int r;
    if (f == 0)
        return _allflush(0);
    _lock_file(f);
    r = _fflush_lk(f);
    _unlock_file(f);
    return r;
}