// _SystemParametersInfoA@16 @ rva 0xd34f2 (6 B) — USER32 import pass-through thunk.
extern void *impSystemParametersInfoA[];
unsigned long __declspec(naked) __stdcall SystemParametersInfoA(void *a, void *b, void *c, void *d)
{
    __asm { jmp dword ptr [impSystemParametersInfoA] }
}
