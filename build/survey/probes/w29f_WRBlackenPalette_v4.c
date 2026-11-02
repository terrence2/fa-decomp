// 0xc51d0 _WRBlackenPalette@12 — v4: naked asm de-asm.
// Wall: CL 4.2 has no C spelling for FA's mul-bl / rep-stosb / loop / early
// arg-load shape (5 variants: /G5, /G4, /G2, /G3, /Oy- all emit imul+stosd
// with lazy arg loads). FA chunk is CRT-flavor codegen (no FPO, ebp frame).
void __declspec(naked) __cdecl WRBlackenPaletteX(void)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push edi
        mov edi, [ebp+8]
        mov ecx, [ebp+12]
        mov ebx, 0x100
        sub ebx, [ebp+16]
        je L9
        cmp ebx, 0x100
        je L7
    L1: mov al, [edi]
        mul bl
        mov [edi], ah
        mov al, [edi+1]
        mul bl
        mov [edi+1], ah
        mov al, [edi+2]
        mul bl
        mov [edi+2], ah
        add edi, 3
        loop L1
    L7: pop edi
        pop ebx
        pop ebp
        ret 12
    L9: mov edx, ecx
        shl ecx, 1
        add ecx, edx
        xor al, al
        rep stosb
        jmp L7
    }
}