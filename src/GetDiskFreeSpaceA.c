// _GetDiskFreeSpaceA@20 @ rva 0xd33fc (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetDiskFreeSpaceA[];
unsigned long __declspec(naked) __stdcall GetDiskFreeSpaceA(void *a, void *b, void *c, void *d, void *e)
{
    __asm { jmp dword ptr [impGetDiskFreeSpaceA] }
}
