/* w40H __aullrem @ 0xdc770 v3 — single shared exit: FA has ONE 5b c2 10 00
 * at +0x71 (reached by the short-path jmp AND by L5's sbb edx,0 fallthrough).
 * v2 duplicated pop/ret (132 B vs 128). */
void __declspec(naked) __cdecl w40hAullRemZ(void)
{
    __asm {
        push ebx
        mov eax, dword ptr [esp+0x14]
        or eax, eax
        jne L1
        mov ecx, dword ptr [esp+0x10]
        mov eax, dword ptr [esp+0x0c]
        xor edx, edx
        div ecx
        mov eax, dword ptr [esp+0x08]
        div ecx
        mov eax, edx
        xor edx, edx
        jmp L2
L1:     mov ecx, eax
        mov ebx, dword ptr [esp+0x10]
        mov edx, dword ptr [esp+0x0c]
        mov eax, dword ptr [esp+0x08]
L3:     shr ecx, 1
        rcr ebx, 1
        shr edx, 1
        rcr eax, 1
        or ecx, ecx
        jne L3
        div ebx
        mov ecx, eax
        mul dword ptr [esp+0x14]
        _emit 0x91
        mul dword ptr [esp+0x10]
        add edx, ecx
        jb L4
        cmp edx, dword ptr [esp+0x0c]
        ja L4
        jb L5
        cmp eax, dword ptr [esp+0x08]
        jbe L5
L4:     sub eax, dword ptr [esp+0x10]
        sbb edx, dword ptr [esp+0x14]
L5:     sub eax, dword ptr [esp+0x08]
        sbb edx, dword ptr [esp+0x0c]
        neg edx
        neg eax
        sbb edx, 0x0
L2:     pop ebx
        ret 0x10
        int 3
        int 3
        int 3
        int 3
        int 3
        int 3
        int 3
        int 3
        int 3
        int 3
        int 3
    }
}