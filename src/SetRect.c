// _SetRect@20 @ rva 0xd3486 (6 B) — USER32 import pass-through thunk.
extern void *impSetRect[];
unsigned long __declspec(naked) __stdcall SetRect(void *a, void *b, void *c, void *d, void *e)
{
    __asm { jmp dword ptr [impSetRect] }
}
