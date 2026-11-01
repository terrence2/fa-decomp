// _MoveFileA@8 @ rva 0xd3450 (6 B) — KERNEL32 import pass-through thunk.
extern void *impMoveFileA[];
unsigned long __declspec(naked) __stdcall MoveFileA(void *a, void *b)
{
    __asm { jmp dword ptr [impMoveFileA] }
}
