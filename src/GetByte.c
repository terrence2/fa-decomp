// _GetByte@4 @ rva 0xd3636 (6 B) — GetByte serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impGetByte[];
unsigned long __declspec(naked) __stdcall GetByte(void *a0)
{
    __asm { jmp dword ptr [impGetByte] }
}
