// _LCMapStringW@24 @ rva 0xe4df6 (6 B) - KERNEL32 import pass-through thunk.
extern void *impLCMapStringW[];
void __declspec(naked) __stdcall LCMapStringW(void)
{
    __asm { jmp dword ptr [impLCMapStringW] }
}
