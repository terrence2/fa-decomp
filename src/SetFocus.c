// _SetFocus@4 @ rva 0xd34ce (6 B) — USER32 import pass-through thunk.
extern void *impSetFocus[];
unsigned long __declspec(naked) __stdcall SetFocus(void *a)
{
    __asm { jmp dword ptr [impSetFocus] }
}
