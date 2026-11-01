// _GetCursorPos@4 @ rva 0xd347a (6 B) — USER32 import pass-through thunk.
extern void *impGetCursorPos[];
unsigned long __declspec(naked) __stdcall GetCursorPos(void *a)
{
    __asm { jmp dword ptr [impGetCursorPos] }
}
