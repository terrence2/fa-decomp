// _SetHandleCount@4 @ rva 0xe4e5c (6 B) - KERNEL32 import pass-through thunk.
extern void *impSetHandleCount[];
void __declspec(naked) __stdcall SetHandleCount(void)
{
    __asm { jmp dword ptr [impSetHandleCount] }
}
