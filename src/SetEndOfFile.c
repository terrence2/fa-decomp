// _SetEndOfFile@4 @ rva 0xe4ece (6 B) - KERNEL32 import pass-through thunk.
extern void *impSetEndOfFile[];
void __declspec(naked) __stdcall SetEndOfFile(void)
{
    __asm { jmp dword ptr [impSetEndOfFile] }
}
