// unnamed chunk @ rva 0xddf10 (25 B) — cdecl(int): (x & 0xffff) == 0x354
// test; returns 0xc04 in ax for a hit, 0 otherwise. 16-bit returns
// (66 b8 / 66 33 c0) suggest a short return type.
short __cdecl w30g_lang354(int x)
{
    if ((x & 0xffff) == 0x354)
        return 0xc04;
    return 0;
}