// __ld12tod @ rva 0xdfce0 (24 B) — CRT 12-byte long-double -> double: forward
//   (pd, ps, static cvt buf) to __ld12cvt.  Right-to-left arg emission with the
//   stack-param fetch hoisted per FA's CRT pattern (mov eax,[esp+8] BEFORE the
//   const push).  map: ldCvtBufQ=__newmode+0x8 (human-coin interior offset).
//   NB: FA's cdecl symbol is __ld12cvt, so the C identifier is _ld12cvt
//   (declaring __ld12cvt mangles to ___ld12cvt and breaks the identity link).
extern void _ld12cvt(char *a, char *b, char *c);
extern char ldCvtBufQ[];

void __cdecl ld12tod(char *pd, char *ps)
{
    _ld12cvt(pd, ps, ldCvtBufQ);
}