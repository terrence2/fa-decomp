// _IsPortAvailable@4 @ rva 0xd3624 (6 B) — IsPortAvailable serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impIsPortAvailable[];
unsigned long __declspec(naked) __stdcall IsPortAvailable(void *a0)
{
    __asm { jmp dword ptr [impIsPortAvailable] }
}
