// _ser_rs232_getpacket@12 @ rva 0xd35ca (6 B) — ser_rs232_getpacket serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impser_rs232_getpacket[];
unsigned long __declspec(naked) __stdcall ser_rs232_getpacket(void *a0, void *a1, void *a2)
{
    __asm { jmp dword ptr [impser_rs232_getpacket] }
}
