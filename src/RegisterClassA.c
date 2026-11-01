// _RegisterClassA@4 @ rva 0xd34e0 (6 B) — USER32 import pass-through thunk.
extern void *impRegisterClassA[];
unsigned long __declspec(naked) __stdcall RegisterClassA(void *a)
{
    __asm { jmp dword ptr [impRegisterClassA] }
}
