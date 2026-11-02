void __declspec(naked) _chkstk(void)
{
    __asm {
        push ecx
        cmp eax, 0x1000
        lea ecx, [esp+8]
        jb small
        big:
        sub ecx, 0x1000
        sub eax, 0x1000
        test dword ptr [ecx], eax
        cmp eax, 0x1000
        jae big
        small:
        sub ecx, eax
        mov eax, esp
        test dword ptr [ecx], eax
        mov esp, ecx
        mov ecx, [eax]
        mov eax, [eax+4]
        push eax
        ret
    }
}
