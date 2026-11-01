/* @EnvHighest@4 @ rva 0x9b4f0 — naked asm (C reg-alloc puts bv/p in swapped regs) */
void __declspec(naked) __fastcall EnvHighest(void)
{
    __asm {
        push ebx
        xor eax, eax
        push esi
        add ecx, 8
        push edi
        mov esi, -1
        movsx edx, word ptr [ecx-6]
        lea ebx, [edx+edx*2]
        lea edi, [ecx+ebx*2-6]
        cmp edi, ecx
        jb exit
    L:
        mov edx, [edi+2]
        cmp esi, edx
        jge skip
        mov esi, edx
        mov eax, edi
    skip:
        sub edi, 6
        cmp edi, ecx
        jae L
    exit:
        pop edi
        pop esi
        pop ebx
        ret
    }
}