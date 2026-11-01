// _GetForegroundWindow@0 @ rva 0xd34b6 (6 B) — USER32 import pass-through thunk.
extern void *impGetForegroundWindow[];
unsigned long __declspec(naked) __stdcall GetForegroundWindow(void)
{
    __asm { jmp dword ptr [impGetForegroundWindow] }
}
