// _GlobalFree@4 @ rva 0xd33a8 (6 B) — KERNEL32 import pass-through thunk.
extern void *impGlobalFree[];
unsigned long __declspec(naked) __stdcall GlobalFree(void *a)
{
    __asm { jmp dword ptr [impGlobalFree] }
}
