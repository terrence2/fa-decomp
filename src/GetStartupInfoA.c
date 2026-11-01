// _GetStartupInfoA@4 @ rva 0xe4dcc (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetStartupInfoA[];
void __declspec(naked) __stdcall GetStartupInfoA(void)
{
    __asm { jmp dword ptr [impGetStartupInfoA] }
}
