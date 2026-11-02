int __declspec(naked) __stdcall MultDiv32(int a, int b, int c)
{
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 4
        push ebx
        push esi
        push edi
        mov eax, [ebp+8]
        imul dword ptr [ebp+0xc]
        idiv dword ptr [ebp+0x10]
        mov [ebp-4], eax
        mov eax, [ebp-4]
        _emit 0xe9
        _emit 0
        _emit 0
        _emit 0
        _emit 0
        pop edi
        pop esi
        pop ebx
        _emit 0xc9
        ret 0xc
    }
}
