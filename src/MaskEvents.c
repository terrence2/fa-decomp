// @MaskEvents@4 @ rva 0x63060 — s = ~((m*2)-2) then a BYTE-and on al
//   (24 fe preserves the high byte; C's s &= 0xfffe emits the 16-bit 66 25,
//   d46, and the byte-pointer form spills — d45) → inline __asm (d72 exact).
extern unsigned short cmdBufPos;

void __fastcall MaskEvents_q(int m)
{
    __asm {
        lea  eax, [ecx*2-2]
        not  ax
        and  al, 0xfe
        mov  cmdBufPos, ax
    }
}
