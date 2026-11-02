// __ismbbkana @ rva 0xdb7e0 (42 B) — MBCS single-byte-kana test CONVERTED
// (band N1, 2026-11-02). The tier0 cmp-mirror wall: FA compares the
// __mbctype+0x104 MBCS codepage word (== 932) directly in memory
// (81 3d <mem> 000003a4); CL 4.2 materializes a1 moffs + 3d imm32 and
// picks its own reg plan (probes v2..v6 all diverged). Fix: plain C
// `if (*(int *)mbcFlag == 0x3a4) if (ismbbType(c,0,3)) return 1; return 0;`
// + one 10->10 B patch: CL a1+3d -> FA 81 3d mem-cmp (DIR32 re-add _mbcFlag
// at site 2; payload dword zero — the addend bakes __mbctype+0x104; the
// 0x3a4 imm32 = 000003a4 is byte-order-sensitive, NOT endi-swapped).
// Shared xor-exit: CL's `if..return 1; return 0` folds to xor eax,eax entry
// matching FA's. _ismbbType is the $FA$_t_4db810 stub (map unchanged).
// Probes: p_1..v6 plain-C failed; n1_ISMbbkana_v1 EXACT.
extern char mbcFlag[];
extern int __cdecl ismbbType(int c, int mask, int flg);

int __cdecl _ismbbkana_q(unsigned int c)
{
    if (*(int *)mbcFlag == 0x3a4)
        if (ismbbType((int)c, 0, 3))
            return 1;
    return 0;
}