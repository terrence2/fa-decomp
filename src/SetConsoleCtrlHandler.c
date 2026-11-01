// _SetConsoleCtrlHandler@8 @ rva 0xe4ed4 (6 B) - KERNEL32 import pass-through thunk.
extern void *impSetConsoleCtrlHandler[];
void __declspec(naked) __stdcall SetConsoleCtrlHandler(void)
{
    __asm { jmp dword ptr [impSetConsoleCtrlHandler] }
}
