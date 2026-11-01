// __ld12tof @ rva 0xdfd00 (24 B) — CRT 12-byte long-double -> float: forward
//   (pd, ps, static cvt buf) to __ld12cvt.  Same shape as __ld12tod.
//   map: ldCvtBufQ=__newmode+0x20 (human-coin interior offset).
//   NB: FA's cdecl symbol is __ld12cvt, so the C identifier is _ld12cvt.
extern void _ld12cvt(char *a, char *b, char *c);
extern char ldCvtBufQ[];

void __cdecl ld12tof(char *pd, char *ps)
{
    _ld12cvt(pd, ps, ldCvtBufQ);
}