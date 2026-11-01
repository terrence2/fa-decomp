// _SetForegroundWindow@4 @ rva 0xd34b0 (6 B) — USER32 import pass-through thunk.
extern void *impSetForegroundWindow[];
unsigned long __declspec(naked) __stdcall SetForegroundWindow(void *a)
{
    __asm { jmp dword ptr [impSetForegroundWindow] }
}
