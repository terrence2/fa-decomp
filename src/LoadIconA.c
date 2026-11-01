// _LoadIconA@8 @ rva 0xd34e6 (6 B) — USER32 import pass-through thunk.
extern void *impLoadIconA[];
unsigned long __declspec(naked) __stdcall LoadIconA(void *a, void *b)
{
    __asm { jmp dword ptr [impLoadIconA] }
}
