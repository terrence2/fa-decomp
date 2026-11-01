extern unsigned long objPtrs[];
__declspec(naked) unsigned short __fastcall HARDNumLoaded(int p1, int p2)
{
    __asm {
        push esi
        and ecx, 0xffff
        mov esi, edx
        shl esi, 4
        mov eax, dword ptr objPtrs[ecx*4]
        add esi, edx
        mov ecx, dword ptr [eax + 0x114]
        add ecx, esi
        pop esi
        mov ax, word ptr [ecx + eax*1 + 4]
        and eax, 0x7fff
        ret
    }
}
