// _ShowCursor@4 @ rva 0xd34c8 (6 B) — USER32 import pass-through thunk.
extern void *impShowCursor[];
unsigned long __declspec(naked) __stdcall ShowCursor(void *a)
{
    __asm { jmp dword ptr [impShowCursor] }
}
