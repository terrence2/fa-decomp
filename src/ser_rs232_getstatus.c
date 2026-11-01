// _ser_rs232_getstatus@8 @ rva 0xd35e8 (6 B) — ser_rs232_getstatus serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impser_rs232_getstatus[];
unsigned long __declspec(naked) __stdcall ser_rs232_getstatus(void *a0, void *a1)
{
    __asm { jmp dword ptr [impser_rs232_getstatus] }
}
