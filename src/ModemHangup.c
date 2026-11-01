// _ModemHangup@4 @ rva 0xd368a (6 B) — ModemHangup serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impModemHangup[];
unsigned long __declspec(naked) __stdcall ModemHangup(void *a0)
{
    __asm { jmp dword ptr [impModemHangup] }
}
