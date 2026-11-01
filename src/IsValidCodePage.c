// _IsValidCodePage@4 @ rva 0xe4e8c (6 B) - KERNEL32 import pass-through thunk.
extern void *impIsValidCodePage[];
void __declspec(naked) __stdcall IsValidCodePage(void)
{
    __asm { jmp dword ptr [impIsValidCodePage] }
}
