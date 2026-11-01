// _ser_rs232_flush@8 @ rva 0xd35d6 (6 B) — ser_rs232_flush serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impser_rs232_flush[];
unsigned long __declspec(naked) __stdcall ser_rs232_flush(void *a0, void *a1)
{
    __asm { jmp dword ptr [impser_rs232_flush] }
}
