/* @G_HFlipBitmap@4 @ rva 0xb4cc0 — naked asm (C reg-alloc swaps esi/edi, caches base in edx) */
void __declspec(naked) __fastcall G_HFlipBitmap(void)
{
    __asm {
        push ebx
        mov eax, [ecx+6]
        push esi
        push edi
        xor edi, edi
        cmp eax, edi
        jle exit
    outer:
        mov eax, [ecx+2]
        mov esi, edi
        imul esi, eax
        add esi, [ecx+10]
        lea eax, [eax+esi-1]
        cmp eax, esi
        jbe bottom
    inner:
        mov dl, [esi]
        mov bl, [eax]
        mov [esi], bl
        inc esi
        mov [eax], dl
        dec eax
        cmp eax, esi
        ja inner
    bottom:
        inc edi
        mov eax, [ecx+6]
        cmp eax, edi
        jg outer
    exit:
        pop edi
        pop esi
        pop ebx
        ret
    }
}