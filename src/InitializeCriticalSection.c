// _InitializeCriticalSection@4 @ rva 0xd3336 (6 B) — KERNEL32 import
// pass-through thunk.
extern void *impInitCS[];
void __declspec(naked) __stdcall InitializeCriticalSection(void *cs)
{
    __asm { jmp dword ptr [impInitCS] }
}
