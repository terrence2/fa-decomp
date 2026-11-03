/* rva 0xbba80 (768640), 48 B - v5: naked-asm escape hatch - FA loads the
   callee into ebx after the arg push and calls [ebx]; CL 4.2 /O2 /G5
   insists on ecx + early load under every C spelling tried (v1-v4). */
void __declspec(naked) __cdecl w34g_objC5(void)
{
    __asm
    {
        mov eax, [esp+0x4]
        push ebx
        push esi
        push 0x1000
        mov esi, [eax+0x12]
        push 0x1
        push eax
        mov ebx, [eax+0x4]
        call DWORD PTR [ebx]
        add esp, 0xc
        mov [esi+0x18], eax
        mov [esi], eax
        mov DWORD PTR [esi+0x4], 0x1000
        pop esi
        pop ebx
        ret
    }
}