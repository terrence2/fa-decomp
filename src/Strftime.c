// _strftime @ rva 0xe11e0 (31 B) — CRT forward into __Strftime with a
// trailing 0 (the 5th, localized? arg). Plain right-to-left C reproduces
// FA's interleave exactly: a4 loaded into eax BEFORE push 0, then each
// next param is fetched at [esp+0x10] shifted by the pushes (a3, a2, a1)
// while the previous push rides a reg — the wave-11 CRT-forward pattern
// generalized to 5 args (probe w16b_3 exact, e8 call + add esp,0x14 + ret).
extern unsigned long __cdecl _Strftime(long a, char *b, char *c, void *d,
                                       long e);

unsigned long strftime(long a, char *b, char *c, void *d)
{
    return _Strftime(a, b, c, d, 0);
}