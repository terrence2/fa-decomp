// 0xbf700 gap chunk (32 B) — v3 naked asm: CL 4.2 fuses the compare (vol load
// folded to cmp mem,imm) and setg-fuses the return; FA keeps the naive shape.
void __declspec(naked) __fastcall w30b_selchk(void)
{
    __asm {
        cmp byte ptr [ecx], 4
        jne L2
        mov eax, [ecx+0x34]
        cmp eax, 0x3a00
        jle L2
        mov al, 1
        ret
L2:     xor al, al
        ret
    }
}