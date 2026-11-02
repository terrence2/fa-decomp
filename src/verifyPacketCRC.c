// ?verifyPacketCRC@@YADAAUSERIAL_PACKET@@@Z @ rva 0x98070 (622704, 48 B) —
//   push esi/edi; esi = param; call computePacketCRC -> edi, call packetCRC
//   -> eax, cmp edi,eax (3b f8), sete cl/mov al,cl (FA's own double-move),
//   pop/pop/ret, char answer.
// EXACT via v7 + 1-B patch (survey t1_verify_v7): CL 4.2 canonicalizes ==
// evaluation order — BOTH operand spellings streamed packetCRC's e8 first,
// so FA's computePacketCRC-first order needs the call in STATEMENT position:
// c1 = computePacketCRC(p); return (char)(c1 == packetCRC(p)); CL then pins
// c1 in edi (8b f8 after the first call, same as FA) and streams the
// second call, but canonicalizes the compare to cmp eax,reg (3b c7) — FA
// has cmp edi,eax (3b f8). Equality is direction-free, so the 1-B patch
// '0x1b,1,f8' restores FA's opcode byte with no polarity change.
// ADDEND lesson: e8 rel32 dwords carry ZERO bytes in any patch/payload —
// the linker computes field = symVA + content - addr_next itself; FA's
// literal rel in the payload would double the displacement.
//
// probes: build/survey/probes/t1_verify_v1.c (no), t1_verify_v2.c (EXACT),
//   t1_verify_v3.c (no) — run: python3 build/survey/hybrid_probe.py
//   build/survey/probes/tier1_b1.json
#include <string.h>
extern unsigned long computePacketCRC(void *p);
extern unsigned long packetCRC(void *p);

char verifyPacketCRC_q(void *p)
{
    unsigned long c1 = computePacketCRC(p);
    return (char)(c1 == packetCRC(p));
}