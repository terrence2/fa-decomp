// _ModemWaitForCall@16 @ rva 0xd365a (6 B) — ModemWaitForCall serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impModemWaitForCall[];
unsigned long __declspec(naked) __stdcall ModemWaitForCall(void *a0, void *a1, void *a2, void *a3)
{
    __asm { jmp dword ptr [impModemWaitForCall] }
}
