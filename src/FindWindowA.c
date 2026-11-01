// _FindWindowA@8 @ rva 0xd34ec (6 B) — USER32 import pass-through thunk.
extern void *impFindWindowA[];
unsigned long __declspec(naked) __stdcall FindWindowA(void *a, void *b)
{
    __asm { jmp dword ptr [impFindWindowA] }
}
