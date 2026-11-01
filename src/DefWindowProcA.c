// _DefWindowProcA@16 @ rva 0xd34bc (6 B) — USER32 import pass-through thunk.
extern void *impDefWindowProcA[];
unsigned long __declspec(naked) __stdcall DefWindowProcA(void *a, void *b, void *c, void *d)
{
    __asm { jmp dword ptr [impDefWindowProcA] }
}
