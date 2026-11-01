// _ModemAttention@4 @ rva 0xd3654 (6 B) — ModemAttention serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impModemAttention[];
unsigned long __declspec(naked) __stdcall ModemAttention(void *a0)
{
    __asm { jmp dword ptr [impModemAttention] }
}
