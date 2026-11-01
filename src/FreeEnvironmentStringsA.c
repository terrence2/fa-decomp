// _FreeEnvironmentStringsA@4 @ rva 0xe4e44 (6 B) - KERNEL32 import pass-through thunk.
extern void *impFreeEnvironmentStringsA[];
void __declspec(naked) __stdcall FreeEnvironmentStringsA(void)
{
    __asm { jmp dword ptr [impFreeEnvironmentStringsA] }
}
