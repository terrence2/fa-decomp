// _RegQueryValueExA@24 @ rva 0xd3696 (6 B) — RegQueryValueExA (ADVAPI32) import pass-through thunk.
extern void *impRegQueryValueExA[];
unsigned long __declspec(naked) __stdcall RegQueryValueExA(void *a0, void *a1, void *a2, void *a3, void *a4, void *a5)
{
    __asm { jmp dword ptr [impRegQueryValueExA] }
}
