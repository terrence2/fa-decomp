// _SetUnhandledExceptionFilter@4 @ rva 0xe4e9e (6 B) - KERNEL32 import pass-through thunk.
extern void *impSetUnhandledExceptionFilter[];
void __declspec(naked) __stdcall SetUnhandledExceptionFilter(void)
{
    __asm { jmp dword ptr [impSetUnhandledExceptionFilter] }
}
