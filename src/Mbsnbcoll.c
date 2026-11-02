// __mbsnbicoll @ rva 0xdb2b0 (897712) — 59 B code, no pad. CL C + 1 patch — EXACT.
// Source probes w24b_mbsnbcoll_v1.c (probes/).
//
// Shape: wrapper over the CRT collate engine (chunk 0xe0500, 749 B, KEEP-ASM
// class: sub esp,0x20, probes kernel32 support then calls CompareStringA via
// IAT or runs the manual MBCS loop; returns 1/2/3). Wrapper: count==0 -> xor
// eax,eax/ret; else 7-arg cdecl call to the engine, add esp,0x1c; result 0 ->
// 0x7fffffff (_NLSCMPERROR), else ret-2. RTL arg list (a1..a7 =
// __mbctype+0x108, 1, [esp+8](=str2), count, [esp+8], count,
// __mbctype+0x104): the engine keys (str, len) pairs via 0xe07f0 and s1 is
// never re-read by the wrapper after entry — FA's own bytes, not an
// interpretation of ours.
//
// Residual CL delta (patch): CL hoists the g2 load as `8b 0d` mov
// ECX,[moffs] before the tail pushes and reuses eax for the second str2
// push; FA loads g2 with `a1` (mov EAX,[moffs]) in situ after the first
// str2 push, reloads str2 from the stack ([esp+0x14] into ECX) for the
// second push, and loads the first str2 copy into EDX before the initial
// push runs. Same arg order either way; pure codegen. Patch @16 (=0x10),
// state toolchain-diff, provenance 'patch 16-37: fa/CL codegen delta in the
// 7-arg RTL arg eval — regchoice+hoist; layout.json chunk 0xdb2b0':
//   --patch '16,18,8b542408505152a100000000518b4c2414516a0150,8:6:__mbcgB'
// (18 CL bytes out to 21 FA bytes; the ,8:6:__mbcgB re-attaches the DIR32
// reloc at span offset 0x8 = FA's a1-moffs site — CL's own 8b0d site fell
// inside the replaced span and is dropped by the patcher.)
//
// Maps (FROM = obj-decorated C names):
//   __mbcgA=__mbctype+0x104   (DIR32; +0x104 addend baked into the moffs
//                              dword: FA content = __mbctype VA + 0x104)
//   __mbcgB=__mbctype+0x108   (DIR32, addend baked; site re-attached by the
//                              patch above)
//   __collw=$FA$_t_4e0500     (REL32; callee cleans its 7 args — wrapper
//                              add esp,0x1c stays)
// Externals after fit: __mbctype, $FA$_t_4e0500 (both in FA universe).
// Tail: none (pad 0). Compiles /c /O2 /Gy /G5, no pragma (FPO chunk).
extern unsigned long _mbcgA;    /* __mbctype+0x104 dword */
extern unsigned long _mbcgB;    /* __mbctype+0x108 dword */
extern int _collw(unsigned long g2, int flag, const unsigned char *x,
                  unsigned int count, const unsigned char *x2,
                  unsigned int count2, unsigned long g1);

int _mbsnbcoll_q(const unsigned char *str1, const unsigned char *str2,
                 unsigned int count)
{
    int r;
    if (count == 0)
        return 0;
    r = _collw(_mbcgB, 1, str2, count, str2, count, _mbcgA);
    if (r == 0)
        return 0x7fffffff;
    return r - 2;
}
