// _FlushTransmitBuffer@4 @ rva 0xd35f4 (6 B) — FlushTransmitBuffer serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impFlushTransmitBuffer[];
unsigned long __declspec(naked) __stdcall FlushTransmitBuffer(void *a0)
{
    __asm { jmp dword ptr [impFlushTransmitBuffer] }
}
