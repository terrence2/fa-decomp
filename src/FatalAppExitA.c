// _FatalAppExitA@8 @ rva 0xe4dde (6 B) - KERNEL32 import pass-through thunk.
extern void *impFatalAppExitA[];
void __declspec(naked) __stdcall FatalAppExitA(void)
{
    __asm { jmp dword ptr [impFatalAppExitA] }
}
