// _MultiByteToWideChar@24 @ rva 0xe4de4 (6 B) - KERNEL32 import pass-through thunk.
extern void *impMultiByteToWideChar[];
void __declspec(naked) __stdcall MultiByteToWideChar(void)
{
    __asm { jmp dword ptr [impMultiByteToWideChar] }
}
