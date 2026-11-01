// _GetFileSize@8 @ rva 0xd337e (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetFileSize[];
unsigned long __declspec(naked) __stdcall GetFileSize(void *a, void *b)
{
    __asm { jmp dword ptr [impGetFileSize] }
}
