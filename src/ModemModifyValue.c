// _ModemModifyValue@12 @ rva 0xd3684 (6 B) — ModemModifyValue serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impModemModifyValue[];
unsigned long __declspec(naked) __stdcall ModemModifyValue(void *a0, void *a1, void *a2)
{
    __asm { jmp dword ptr [impModemModifyValue] }
}
