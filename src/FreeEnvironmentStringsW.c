// _FreeEnvironmentStringsW@4 @ rva 0xe4e50 (6 B) - KERNEL32 import pass-through thunk.
extern void *impFreeEnvironmentStringsW[];
void __declspec(naked) __stdcall FreeEnvironmentStringsW(void)
{
    __asm { jmp dword ptr [impFreeEnvironmentStringsW] }
}
