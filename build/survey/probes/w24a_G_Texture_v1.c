extern void __cdecl MMAccessW(void);
extern void __cdecl G__Texture(void);

void __declspec(naked) __stdcall G_Texture(int eaxp, int edxp, int stackp)
{
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 8
        push ebx
        mov [ebp-4], edx
        push esi
        push edi
        call MMAccessW
        mov [ebp-8], eax
        _emit 0x60
        mov esi, [ebp-8]
        mov eax, [ebp-4]
        mov ebx, [ebp+8]
        call G__Texture
        _emit 0x61
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret 4
    }
}
