// _MessageBoxA@16 @ rva 0xd348c (6 B) — USER32 import pass-through thunk.
extern void *impMessageBoxA[];
unsigned long __declspec(naked) __stdcall MessageBoxA(void *a, void *b, void *c, void *d)
{
    __asm { jmp dword ptr [impMessageBoxA] }
}
