// _IsCarrierDetect@4 @ rva 0xd3648 (6 B) — IsCarrierDetect serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impIsCarrierDetect[];
unsigned long __declspec(naked) __stdcall IsCarrierDetect(void *a0)
{
    __asm { jmp dword ptr [impIsCarrierDetect] }
}
