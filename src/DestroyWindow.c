// _DestroyWindow@4 @ rva 0xd34a4 (6 B) — USER32 import pass-through thunk.
extern void *impDestroyWindow[];
unsigned long __declspec(naked) __stdcall DestroyWindow(void *a)
{
    __asm { jmp dword ptr [impDestroyWindow] }
}
