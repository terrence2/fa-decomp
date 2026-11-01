// _DeleteCriticalSection@4 @ rva 0xd333c (6 B) — KERNEL32 import
// pass-through thunk.
extern void *impDeleteCS[];
void __declspec(naked) __stdcall DeleteCriticalSection(void *cs)
{
    __asm { jmp dword ptr [impDeleteCS] }
}
