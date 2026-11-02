// _isalnum @ rva 0xd4200 (50 B) — MBCS-gated ctype test, tier0 Isctype
// family (a) CONVERTED (band N1, 2026-11-02). The tier0 wall: FA tests the
// __ctype+0x204 MBCS max directly in memory (83 3d mem-cmp) and indexes
// __pctype with an and-mask; CL 4.2 always materializes the load (a1 moffs +
// cmp eax,imm) and the reg plan diverges. The Ispunct recipe generalized to
// every mask: plain C `if (*(int *)ctype204 > 1) return _isctype(c, MASK);
// return _pctype[c] & MASK;` + 4 one-field patches:
//   patch 0: head 8->7B, CL a1+3d materialized compare -> FA 83 3d mem-cmp
//     (DIR32 re-add _ctype204 at site 2; payload dword zero — addend bakes).
//   patch 0xa: modrm reg fix (CL used eax; FA dec-reg 4c).
//   patch 0x12: push-mask reg fix (FA 51 = ecx).
//   patch 0x1c: tail rewrite 18->20 B (imm32 mask): CL's mov [regs]/and -> FA
//     8b 15 __pctype / 33 c0 / 8b 4c 24 04 / 66 8b 04 4a / and eax,0x107 (imm32) / c3
//     (DIR32 re-add __pctype at site 2; __pctype IS the FA chunk name so the
//     map bakes nothing; the imm32 masks arrive via 25 07 01 00 00).
// Probes: p_w23_Isisalnum* plain-C failed, n1_Isalnum_v1 EXACT.
extern char ctype204[];
extern unsigned short *_pctype;
extern int __cdecl _isctype(int c, int mask);

int __cdecl isalnum(int c)
{
    if (*(int *)ctype204 > 1)
        return _isctype(c, 0x107);
    return _pctype[c] & 0x107;
}
