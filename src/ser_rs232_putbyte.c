// _ser_rs232_putbyte@8 @ rva 0xd35e2 (6 B) — ser_rs232_putbyte serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impser_rs232_putbyte[];
unsigned long __declspec(naked) __stdcall ser_rs232_putbyte(void *a0, void *a1)
{
    __asm { jmp dword ptr [impser_rs232_putbyte] }
}
