// _ClipCursor@4 @ rva 0xd3480 (6 B) — USER32 import pass-through thunk.
extern void *impClipCursor[];
unsigned long __declspec(naked) __stdcall ClipCursor(void *a)
{
    __asm { jmp dword ptr [impClipCursor] }
}
