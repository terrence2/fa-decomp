// __i64toa @ rva 0xe1fc0 (925632) — 61 B code, no pad. CL C + 1 patch — EXACT.
// Source probes w24b_i64toa_v1.c..v3.c (probes/).
//
// Lever: worker is __stdcall with the 64-bit value as its FIRST parameter.
// Declaring `extern char *__stdcall _W(T64 val, char *buf, int radix, int neg)`
// makes CL push the halves hi-then-lo at RTL arg evaluation — after
// push neg / push radix / push buf — which is FA's exact 5-push order and
// (callee cleans, ret 0x14 verified in chunk 0xe2000's tail) explains why FA
// has no caller-side esp adjust. Passing val whole (not (val>>32)) keeps CL
// off the __aullshr helper: it just mov-loads [esp+8] / [esp+4] to push.
//
// Residual CL delta (the only thing v3/v2 couldn't reach and the patch fixes):
// the neg diamond. C `neg = radix == 10 && (__int64)val < 0;` compiles to the
// SHORT form (mov ecx,[esp+0xc]; 85 c9; jg/mov ecx,1/jl/xor — 17 B), but FA
// carries CL's unsimplified 64-bit SLT-0 mem expansion (25 B):
//   cmp [esp+0xc],0 / jg L / jl T / cmp [esp+8],0 / jae L / mov ecx,1 / jmp M / xor: M
// where the cmp-lo branch against imm 0 is always-taken and the mov ecx,1
// fallthrough is dead — FA simply was never re-passed the folded form.
// Patch @0x8 (state toolchain-diff, provenance 'patch 0x8-0x20: FA diamond is
// CL4.2 unsimplified __int64<0 mem-expansion; CL /O2 on unsigned T64 folds to
// 17B reg-test; offsets from layout.json probe w24b_i64toa_v2'):
//   --patch '8,17,7517837c240c007f107c07837c2408007307b901000000eb02'
// (17 B out to FA's 25 B; everything from 0x21 on shifts +8 and is byte-equal;
// the call reloc @53 shifts onto FA's e8 site automatically.)
//
// Maps: __i64toa_w@20 -> $FA$_t_4e2000 (worker chunk; rel32 call disp is
// fixup-resolved: FA content 7 = 0xe2000 - 0xe1ff9).
// Tail: none (pad 0).
typedef unsigned __int64 T64;
extern char *__stdcall _i64toa_w(T64 val, char *buf, int radix, int neg);
/* obj symbol _i64toa_w@20 -> $FA$_t_4e2000 */

char *_i64toa_q(T64 val, char *buf, int radix)
{
    int neg;
    neg = radix == 10 && (__int64)val < 0;
    _i64toa_w(val, buf, radix, neg);
    return buf;
}
