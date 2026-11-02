// __strncmp @ rva 0xd4990 — naked asm v1
__declspec(naked) int __cdecl strncmpq(const char *first, const char *last, unsigned long count)
{
    __asm
    {
        push ebp
        mov ebp, esp
        push edi
        push esi
        push ebx
        mov ecx, [ebp+10h]
        jecxz done
        mov ebx, ecx
        mov edi, [ebp+8]
        mov esi, edi
        xor eax, eax
        repne scasb
        neg ecx
        add ecx, ebx
        mov edi, esi
        mov esi, [ebp+12]
        repe cmpsb
        mov al, [esi-1]
        xor ecx, ecx
        cmp al, [edi-1]
        ja fold
        je done
        dec ecx
        dec ecx
    fold:
        not ecx
    done:
        mov eax, ecx
        pop ebx
        pop esi
        pop edi
        leave
        ret
    }
}
