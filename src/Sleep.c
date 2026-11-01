// _Sleep@4 @ rva 0xd332a (6 B) — KERNEL32 import pass-through thunk.
extern void *impSleep[];
void __declspec(naked) __stdcall Sleep(unsigned long ms)
{
    __asm { jmp dword ptr [impSleep] }
}
