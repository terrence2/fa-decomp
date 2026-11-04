// @MaskEvents@4 @ rva 0x63060 (32 B: 0x20 = 0x13 code + 0x0d census tail
// 8d9b00..8da424..) — cmdBufPos &= m*2 fold CONVERTED (survey closeout
// wave t4, 2026-11-02). Old wall: partial-byte-written 16-bit value in AX —
// FA does not ax (66 f7 d0) then a FUSED byte-and and al,0xfe (24 fe);
// CL 4.2 always canonicalizes s &= 0xfffe to and ax,0xfffe (66 25 fe ff),
// regardless of mask width (32-bit ~1u proven identical, t4_mask_v1;
// byte-pointer/union/separate-byte spellings spill, v4/v5/v6).
// C form (1-patch hybrid): plain C v1 stream reproduced everything else —
//   lea eax,[ecx*2-2] / not ax / and ax,0xfffe <-> FA and al,0xfe /
//   66 a3 mov [cmdBufPos],ax (moffs) / ret
// + one patch 10,4,24fe: 4->2 B over the and; the moffs DIR32 reloc shifts
// 0x0e->0x0c automatically; addend bakes via map _cmdBufPos=_curThing+0x58.
// Probes: d45/d72 naked asm (tier-0 cookbook: and al,imm8 unreachable in
// this CL revision); t4_mask_v1 wall-proof; t4_mask_h1 EXACT.
extern unsigned short cmdBufPos;

void __fastcall MaskEvents_q(int m)
{
    unsigned short s;

    s = m * 2 - 2;
    s = ~s;
    s &= 0xfffe;
    cmdBufPos = s;
}