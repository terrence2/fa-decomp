// _CompareStringW@24 @ rva 0xe4ebc (6 B) - KERNEL32 import pass-through thunk.
extern void *impCompareStringW[];
void __declspec(naked) __stdcall CompareStringW(void)
{
    __asm { jmp dword ptr [impCompareStringW] }
}
