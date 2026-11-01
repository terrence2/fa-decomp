// _CompareStringA@24 @ rva 0xe4eb6 (6 B) - KERNEL32 import pass-through thunk.
extern void *impCompareStringA[];
void __declspec(naked) __stdcall CompareStringA(void)
{
    __asm { jmp dword ptr [impCompareStringA] }
}
