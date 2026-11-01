extern unsigned long cmStopTop;
extern unsigned long wngStopTop;
extern void *__fastcall MMReallocPtr(int a, int b);
__declspec(naked) void __stdcall OBJStopAdding(void)
{
    __asm {
        mov edx, dword ptr [cmStopTop]
        mov ecx, dword ptr [wngStopTop]
        sub edx, ecx
        call MMReallocPtr
        test eax, eax
        jz fin
        mov dword ptr [wngStopTop], eax
        fin: ret
    }
}
