// _CreateWindowExA@48 @ rva 0xd34d4 (6 B) — USER32 import pass-through thunk.
extern void *impCreateWindowExA[];
unsigned long __declspec(naked) __stdcall CreateWindowExA(void *a, void *b, void *c, void *d, void *e, void *f, void *g, void *h, void *i, void *j, void *k, void *l)
{
    __asm { jmp dword ptr [impCreateWindowExA] }
}
