// _RegOpenKeyExA@20 @ rva 0xd369c (6 B) — RegOpenKeyExA (ADVAPI32) import pass-through thunk.
extern void *impRegOpenKeyExA[];
unsigned long __declspec(naked) __stdcall RegOpenKeyExA(void *a0, void *a1, void *a2, void *a3, void *a4)
{
    __asm { jmp dword ptr [impRegOpenKeyExA] }
}
