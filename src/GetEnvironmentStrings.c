// _GetEnvironmentStrings@0 @ rva 0xe4e4a (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetEnvironmentStrings[];
void __declspec(naked) __stdcall GetEnvironmentStrings(void)
{
    __asm { jmp dword ptr [impGetEnvironmentStrings] }
}
