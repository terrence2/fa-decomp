// _GetFileTime@16 @ rva 0xd3414 (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetFileTime[];
unsigned long __declspec(naked) __stdcall GetFileTime(void *a, void *b, void *c, void *d)
{
    __asm { jmp dword ptr [impGetFileTime] }
}
