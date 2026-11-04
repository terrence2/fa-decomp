// _ungetc @ rva 0xe01c0 (45 B) — int _ungetc(int c, FILE *f): lock the
// FILE, __ungetc_lk(c,f) under it, unlock, return. f rides edi, c loaded
// from [esp+0x10] after the lock call, result in esi (probe w13c_ungetc1
// exact).
extern void __cdecl _lock_file(void *f);
extern int __cdecl _ungetc_lk(int c, void *f);
extern void __cdecl _unlock_file(void *f);

int __cdecl _ungetc(int c, void *f)
{
    int r;
    _lock_file(f);
    r = _ungetc_lk(c, f);
    _unlock_file(f);
    return r;
}