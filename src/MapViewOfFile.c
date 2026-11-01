// _MapViewOfFile@20 @ rva 0xd3372 (6 B) — KERNEL32 import pass-through thunk.
extern void *impMapViewOfFile[];
unsigned long __declspec(naked) __stdcall MapViewOfFile(void *a, void *b, void *c, void *d, void *e)
{
    __asm { jmp dword ptr [impMapViewOfFile] }
}
