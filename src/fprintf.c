// _fprintf @ rva 0xd5ce0 (73 B, FPO fpo/esp params=2) — CRT fprintf:
// lock the stream (esi = 1st param), __stbuf redirects the FILE if it's
// stdout/stderr (returns the real stream -> edi), build the in-frame
// va_list (lea eax,[esp+0x18] = first variadic), call the dopr engine
// (3 args: stream, fmt, arglist), save the char count in ebx, flush
// (esi,edi) via the flush helper, unlock, return ebx. EXACT as plain C
// (wave-23 probe, first spelling): the naked-asm "odd push edi/push esi
// reserve slot" is just FA's CL deferring the edi callee-save to the
// arg-push stream; our CL saves edi in the prologue instead and the
// esp-relative constants ([esp+0xc] esi-load, [esp+0x18] fmt + va_start)
// come out identical either way.
// Maps: _lockFileX=__lock_file, _stbufX=__stbuf, _doprX=$FA$_t_4d6610,
// _flushX=$FA$_t_4da510, _unlockFileX=__unlock_file.
#include <stdarg.h>
extern void lockFileX(void *stream);
extern void *stbufX(void *stream);
extern int doprX(void *stream, const char *fmt, char *arglist);
extern void flushX(void *os, void *stream);
extern void unlockFileX(void *stream);

int __cdecl fprintfQ(void *stream, const char *fmt, ...)
{
    va_list arglist;
    void *os;
    int n;
    lockFileX(stream);
    os = stbufX(stream);
    va_start(arglist, fmt);
    n = doprX(stream, fmt, arglist);
    flushX(os, stream);
    unlockFileX(stream);
    return n;
}