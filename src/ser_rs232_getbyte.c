// _ser_rs232_getbyte@8 @ rva 0xd35dc (6 B) — ser_rs232_getbyte serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impser_rs232_getbyte[];
unsigned long __declspec(naked) __stdcall ser_rs232_getbyte(void *a0, void *a1)
{
    __asm { jmp dword ptr [impser_rs232_getbyte] }
}
