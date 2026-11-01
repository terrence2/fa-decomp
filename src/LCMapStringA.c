// _LCMapStringA@24 @ rva 0xe4dea (6 B) - KERNEL32 import pass-through thunk.
extern void *impLCMapStringA[];
void __declspec(naked) __stdcall LCMapStringA(void)
{
    __asm { jmp dword ptr [impLCMapStringA] }
}
