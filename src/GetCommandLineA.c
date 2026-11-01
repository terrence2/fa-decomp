// _GetCommandLineA@0 @ rva 0xe4dd2 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetCommandLineA[];
void __declspec(naked) __stdcall GetCommandLineA(void)
{
    __asm { jmp dword ptr [impGetCommandLineA] }
}
