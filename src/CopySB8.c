void __declspec(naked) CopySB8(void *src, void *dst, int step)
{
    __asm {
        push ebp
        mov ebp, esp
        _emit 0x60
        mov ebx, [ebp + 8]
        mov edx, [ebp + 0xc]
        mov ecx, [ebp + 0x10]
        _emit 0x50
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, ecx
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, ecx
        mov eax, [ebx]
        mov [edx], eax
        add ebx, 4
        add edx, ecx
        mov eax, [ebx]
        mov [edx], eax
        _emit 0x58
        _emit 0x61
        pop ebp
        ret
    }
}