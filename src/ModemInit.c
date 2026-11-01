// _ModemInit@4 @ rva 0xd364e (6 B) — ModemInit serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impModemInit[];
unsigned long __declspec(naked) __stdcall ModemInit(void *a0)
{
    __asm { jmp dword ptr [impModemInit] }
}
