// _CdrvCrc16@8 @ rva 0xd3642 (6 B) — CdrvCrc16 serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impCdrvCrc16[];
unsigned long __declspec(naked) __stdcall CdrvCrc16(void *a0, void *a1)
{
    __asm { jmp dword ptr [impCdrvCrc16] }
}
