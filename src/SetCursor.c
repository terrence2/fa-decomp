// _SetCursor@4 @ rva 0xd34aa (6 B) — USER32 import pass-through thunk.
extern void *impSetCursor[];
unsigned long __declspec(naked) __stdcall SetCursor(void *a)
{
    __asm { jmp dword ptr [impSetCursor] }
}
