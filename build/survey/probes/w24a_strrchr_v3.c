__declspec(naked) char *__cdecl strrchr_probe(const char *s, int ch)
{
    __asm {
        push ebp
        mov ebp, esp
        push edi
        mov edi, [ebp+8]
        xor eax, eax
        or ecx, -1
        repnz scasb
        inc ecx
        neg ecx
        dec edi
        mov al, [ebp+0xc]
        std
        repnz scasb
        inc edi
        cmp byte ptr [edi], al
        je found
        xor eax, eax
        jmp skipover
        found:
        mov eax, edi
        skipover:
        cld
        pop edi
        _emit 0xc9
        ret
    }
}
