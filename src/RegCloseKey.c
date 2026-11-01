// _RegCloseKey@4 @ rva 0xd3690 (6 B) — RegCloseKey (ADVAPI32) import pass-through thunk.
extern void *impRegCloseKey[];
unsigned long __declspec(naked) __stdcall RegCloseKey(void *a0)
{
    __asm { jmp dword ptr [impRegCloseKey] }
}
