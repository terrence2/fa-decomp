// _GetEnvironmentStringsW@0 @ rva 0xe4e56 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetEnvironmentStringsW[];
void __declspec(naked) __stdcall GetEnvironmentStringsW(void)
{
    __asm { jmp dword ptr [impGetEnvironmentStringsW] }
}
