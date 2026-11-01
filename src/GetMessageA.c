// _GetMessageA@16 @ rva 0xd349e (6 B) — USER32 import pass-through thunk.
extern void *impGetMessageA[];
unsigned long __declspec(naked) __stdcall GetMessageA(void *a, void *b, void *c, void *d)
{
    __asm { jmp dword ptr [impGetMessageA] }
}
