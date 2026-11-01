// @MAPSetSide@4 @ rva 0x21e40 — byte p[9] = (p[9] & 0x7f) | nationSides[0].
//   The C form folds the index (moffs load, probe d40); FA keeps a live
//   zeroed eax index so the leaf is inline __asm (d41 exact).
extern unsigned char nationSides[];

void __fastcall MAPSetSide_q(int a)
{
    __asm {
        mov  dl, [ecx+9]
        xor  eax, eax
        and  dl, 0x7f
        mov  al, dl
        mov  [ecx+9], dl
        mov  al, nationSides[eax]
        or   al, dl
        mov  [ecx+9], al
    }
}
