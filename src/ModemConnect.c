// _ModemConnect@4 @ rva 0xd3678 (6 B) — ModemConnect serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impModemConnect[];
unsigned long __declspec(naked) __stdcall ModemConnect(void *a0)
{
    __asm { jmp dword ptr [impModemConnect] }
}
