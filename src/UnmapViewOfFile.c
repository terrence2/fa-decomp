// _UnmapViewOfFile@4 @ rva 0xd3396 (6 B) — KERNEL32 import pass-through thunk.
extern void *impUnmapViewOfFile[];
unsigned long __declspec(naked) __stdcall UnmapViewOfFile(void *a)
{
    __asm { jmp dword ptr [impUnmapViewOfFile] }
}
