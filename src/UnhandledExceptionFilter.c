// _UnhandledExceptionFilter@4 @ rva 0xe4e3e (6 B) - KERNEL32 import pass-through thunk.
extern void *impUnhandledExceptionFilter[];
void __declspec(naked) __stdcall UnhandledExceptionFilter(void)
{
    __asm { jmp dword ptr [impUnhandledExceptionFilter] }
}
