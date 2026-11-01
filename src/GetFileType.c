// _GetFileType@4 @ rva 0xe4e62 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetFileType[];
void __declspec(naked) __stdcall GetFileType(void)
{
    __asm { jmp dword ptr [impGetFileType] }
}
