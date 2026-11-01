// _ModemGetCarrierSpeed@4 @ rva 0xd3672 (6 B) — ModemGetCarrierSpeed serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impModemGetCarrierSpeed[];
unsigned long __declspec(naked) __stdcall ModemGetCarrierSpeed(void *a0)
{
    __asm { jmp dword ptr [impModemGetCarrierSpeed] }
}
