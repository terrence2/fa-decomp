// _SetDlgItemTextA@12 @ rva 0xd34f8 (6 B) — USER32 import pass-through thunk.
extern void *impSetDlgItemTextA[];
unsigned long __declspec(naked) __stdcall SetDlgItemTextA(void *a, void *b, void *c)
{
    __asm { jmp dword ptr [impSetDlgItemTextA] }
}
