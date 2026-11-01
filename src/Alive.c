// @Alive@4 @ rva 0x73710 (64 B) — fastcall thunk ptr in ecx: unaligned dword
//   load [ecx+1] with byte tests a8 01 / f6 c4 20, word field +0xe gate, then
//   [ecx] type 2/4 dispatch (je over the second cmp into a shared +0xe3
//   truth block: mov al,[ecx+0xe3] / test / jne -> return 1 / xor al / ret /
//   b0 01 / ret).  The truth body is CL-unfoldable (every C form folded to
//   cmp mem,0 + setne in ~3 rounds, w12b_Alive/-2) — naked asm (w12b_Alive3
//   byte-exact).
__declspec(naked) char Alive_q(void)
{
    __asm {
        mov eax, [ecx + 1]
        test al, 1
        jne L1
        xor al, al
        ret
    L1:
        cmp word ptr [ecx + 0xe], 0
        jne L2
        xor al, al
        ret
    L2:
        test ah, 0x20
        je L3
        xor al, al
        ret
    L3:
        mov al, [ecx]
        cmp al, 2
        je L4
        cmp al, 4
        jne L5
    L4:
        mov al, [ecx + 0xe3]
        test al, al
        jne L5
        xor al, al
        ret
    L5:
        mov al, 1
        ret
    }
}