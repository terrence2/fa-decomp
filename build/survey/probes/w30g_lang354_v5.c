// v5 — same body as v1/v2; the branchy FA shape is unreachable from source
// (CL 4.2 folds the constant-arm return select into sub/cmp1/sbb/and,
// wave-28 canonicalization wall: v1..v4 all emit identical bytes). The
// toolchain-diff patch rewrites offsets 9..0x17 with FA's 16-byte
// branchy tail: cmp eax,0x354 / je +4 / xor ax,ax / ret / mov ax,0xc04 / ret.
short __cdecl w30g_lang354(int x)
{
    if ((x & 0xffff) == 0x354)
        return 0xc04;
    return 0;
}