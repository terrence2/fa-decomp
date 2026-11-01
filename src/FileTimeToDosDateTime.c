// _FileTimeToDosDateTime@12 @ rva 0xd3408 (6 B) — KERNEL32 import pass-through thunk.
extern void *impFileTimeToDosDateTime[];
unsigned long __declspec(naked) __stdcall FileTimeToDosDateTime(void *a, void *b, void *c)
{
    __asm { jmp dword ptr [impFileTimeToDosDateTime] }
}
