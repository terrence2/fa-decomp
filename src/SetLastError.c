// _SetLastError@4 @ rva 0xe4e14 (6 B) - KERNEL32 import pass-through thunk.
extern void *impSetLastError[];
void __declspec(naked) __stdcall SetLastError(void)
{
    __asm { jmp dword ptr [impSetLastError] }
}
