// w40G_db1f0_v1 — unnamed chunk @ rva 0xdb1f0 (62 B, 1 param cdecl,
// MBCS-gated ctype test, tier0 Isctype family). FA: 83 3d mem-cmp of
// __ctype+0x204 vs 1; jle -> __pctype[c]&4 table path; fallthrough ->
// _isctype(c,4); both paths test 4-bit: nonzero -> return c; else return
// ((c & ~0x20) - 7). Isalpha recipe (src/Isalpha.c) generalized.
extern char ctype204[];
extern unsigned short *_pctype;
extern int __cdecl _isctype(int c, int mask);

int __cdecl w40g_cty(int c)
{
    long r;
    if (*(int *)ctype204 > 1)
        r = _isctype(c, 4);
    else
        r = _pctype[c] & 4;
    if (r != 0)
        return c;
    return (c & ~0x20) - 7;
}