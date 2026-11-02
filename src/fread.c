// _fread @ rva 0xd5680 (55 B, FPO fpo/esp params=4) — CRT fread: lock the
// stream, call __fread_lk, unlock, return the count. EXACT as plain C
// (wave-23 probe): CL 10.20.6166 compiles the three-call wrapper with the
// stream held in esi, the result saved in edi and __cdecl ret with no FPO
// prolog delta; the old "arg-shuffle register plan" was a naked-asm
// over-conservatism — the plan falls out of the natural C spelling.
// Maps: _lockFileX=__lock_file, _freadLkX=__fread_lk, _unlockFileX=__unlock_file.
extern void lockFileX(void *s);
extern unsigned long freadLkX(void *buf, unsigned long size, unsigned long count,
                              void *s);
extern void unlockFileX(void *s);

unsigned long __cdecl freadQ(void *buf, unsigned long size, unsigned long count,
                             void *stream)
{
    unsigned long r;
    lockFileX(stream);
    r = freadLkX(buf, size, count, stream);
    unlockFileX(stream);
    return r;
}