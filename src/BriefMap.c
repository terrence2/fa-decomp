// __BriefMap@4 @ rva 0x7ebf0 (64 B) — FA asm: a0 <_doScreens> / 84 c0 /
//   74 21 / a0 <_doBriefMap> / 84 c0 / 74 18 (if (!doScreens ||
//   !doBriefMap) -> else-path) / call $FA$_t_4225b1 (0-arg helper returning
//   the current brief-page flag in al) / mov ecx,[esp+4] / 3c 01 / 88 01
//   (*p = v — CL emits the ?: compare BEFORE the store) / 1b c0 / 83 e0 fe
//   / 83 c0 0d / c2 04 00; else-path: 80 39 01 / 1b c0 / 83 e0 fe / 83 c0
//   0d / c2 04 00. Both paths end in the borrow-materialized choice
//   v>=1 ? 13 : 11 (d64 family: sbb = -CF, and -2 = -2*CF, +0xd), with the
//   two tails DUPLICATED — the two separate returns keep CL from merging.
// Plain C exact (probe b19c_bm_a; the unsigned-char reads give the cmp,1
//   + sbb tail while the signed-char spelling gives mov 7d/b8 — wave-2
//   polarity lesson; tail = census 8d 64 24 00).
extern char doScreens;
extern char doBriefMap;
extern char briefHelper(void);   /* $FA$_t_4225b1: brief-mode state probe */

long __stdcall _BriefMap(char *p)
{
    unsigned char v;
    if (!doScreens || !doBriefMap)
        return *(unsigned char *)p >= 1 ? 13 : 11;
    v = briefHelper();
    *p = v;
    return v >= 1 ? 13 : 11;
}