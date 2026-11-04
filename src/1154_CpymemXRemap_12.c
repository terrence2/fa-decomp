// _CpymemXRemap@12 @ rva 0xc2be8 — naked asm v2 (full body)
extern unsigned long snowHighT[];

__declspec(naked) void __stdcall CpymemXRemapv2(unsigned long *src, unsigned long *dst, unsigned long n)
{
    __asm
    {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi
        mov esi, [ebp+8]
        mov edi, [ebp+0xc]
        mov ecx, [ebp+0x10]
        xor eax, eax
        xor edx, edx
        L1w26b:
        mov al, [esi]
        cmp al, 0ffh
        je L2w26b
        mov ebx, snowHighT[eax*4]
        mov dl, [edi]
        mov al, [edx+ebx]
        mov [edi], al
        L2w26b:
        inc esi
        inc edi
        dec ecx
        jne L1w26b
        pop edi
        pop esi
        pop ebx
        pop ebp
        ret 0ch
    }
}
