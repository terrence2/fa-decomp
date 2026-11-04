// _LimitAngle@12 @ rva 0x12b30 = 76592, 80 B (stdcall 3 dwords; FA pushes
// ebx/esi/edi with the si=p1-word read BETWEEN push esi and push edi; plain C
// (w25c_LimitAngle_v1) emitted push ebp + an inlined 16-bit-and abs instead of
// FA's extern call @Abs@4 with ecx=ebx, the 8bcb/0fbfd1/668937 reg plan and
// the early shared-epilogue jmp -> naked asm escape, byte-exact incl.
// the 2x8da42400000000 pad).
//
// FA asm (rva 0x12b30, rel @0x14 call -> @Abs@4):
//   53 / 56 / 66 8b 74 24 10 (si=p1) / 57 / 8b 7c 24 10 (edi=p2) /
//   66 8b 1f (bx=[edi]) / 66 2b de (bx-=si) / 8b cb (ecx=ebx) /
//   e8 <@Abs@4> / 66 8b 4c 24 18 (cx=p3) / 0f bf d1 / 3b c2 / 7e 17 (<= pl)
//   / 66 85 db / 7c 0c (jl neg) / 66 03 f1 / 66 89 37 /
//   5f 5e 5b c2 0c 00 / neg: 66 2b f1 / 66 89 37 / 5f 5e 5b c2 0c 00
extern int __fastcall AbsSlewQ(int v);
/* map @AbsSlewQ@4=@Abs@4 */

__declspec(naked) void __stdcall w25c_LimitAngle_q(unsigned short *angle,
                                                   unsigned int val,
                                                   unsigned int plimit)
{
    __asm {
        push ebx
        push esi
        mov   si, WORD PTR [esp + 0x10]
        push  edi
        mov   edi, DWORD PTR [esp + 0x10]
        mov   bx, WORD PTR [edi]
        sub   bx, si
        mov   ecx, ebx
        call  AbsSlewQ
        mov   cx, WORD PTR [esp + 0x18]
        movsx edx, cx
        cmp   eax, edx
        jle   L_epil
        test  bx, bx
        jl    L_neg
        add   si, cx
        mov   WORD PTR [edi], si
        pop   edi
        pop   esi
        pop   ebx
        ret   0x000c
    L_neg:
        sub   si, cx
        mov   WORD PTR [edi], si
    L_epil:
        pop   edi
        pop   esi
        pop   ebx
        ret   0x000c
    }
}