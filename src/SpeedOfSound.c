// @SpeedOfSound@4 @ rva 0x12510 — FA caps alt>>8 at 0x8ca0, scales by the
//   [ecx+ecx*8]/[ecx+eax*4] sib pair («2 = x148) and divides: -(148*
//   (alt>>8)) / 0x8ca0 + 0x45b; C constant-mult folds to 5x«3 (d95) —
//   inline __asm (probe d116 exact).
int __fastcall SpeedOfSound_q(int a)
{
    __asm {
        sar  ecx, 8
        cmp  ecx, 0x8ca0
        jle  sos_cap
        mov  ecx, 0x8ca0
    sos_cap:
        lea  eax, [ecx+ecx*8]
        lea  eax, [ecx+eax*4]
        mov  ecx, 0x8ca0
        shl  eax, 2
        neg  eax
        cdq
        idiv ecx
        add  eax, 0x45b
    }
}
