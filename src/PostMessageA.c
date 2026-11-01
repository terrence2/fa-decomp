// _PostMessageA@16 @ rva 0xd346e (6 B) — USER32 import pass-through thunk.
extern void *impPostMessageA[];
unsigned long __declspec(naked) __stdcall PostMessageA(void *a, void *b, void *c, void *d)
{
    __asm { jmp dword ptr [impPostMessageA] }
}
