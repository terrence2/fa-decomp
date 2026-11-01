// _FreeLibrary@4 @ rva 0xd3420 (6 B) — KERNEL32 import pass-through thunk.
extern void *impFreeLibrary[];
unsigned long __declspec(naked) __stdcall FreeLibrary(void *a)
{
    __asm { jmp dword ptr [impFreeLibrary] }
}
