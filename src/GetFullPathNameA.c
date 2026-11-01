// _GetFullPathNameA@16 @ rva 0xe4dc0 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetFullPathNameA[];
void __declspec(naked) __stdcall GetFullPathNameA(void)
{
    __asm { jmp dword ptr [impGetFullPathNameA] }
}
