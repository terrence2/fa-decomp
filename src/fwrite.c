// _fwrite @ rva 0xd5810 (55 B, FPO fpo/esp params=4) — CRT fwrite: lock the
// stream, call __fwrite_lk, unlock, return the count. EXACT as plain C
// (wave-23 probe), twin of fread.c with the mid call targeting __fwrite_lk.
// Maps: _lockFileX=__lock_file, _fwriteLkX=__fwrite_lk, _unlockFileX=__unlock_file.
extern void lockFileX(void *s);
extern unsigned long fwriteLkX(void *buf, unsigned long size, unsigned long count,
                               void *s);
extern void unlockFileX(void *s);

unsigned long __cdecl fwriteQ(void *buf, unsigned long size, unsigned long count,
                              void *stream)
{
    unsigned long r;
    lockFileX(stream);
    r = fwriteLkX(buf, size, count, stream);
    unlockFileX(stream);
    return r;
}