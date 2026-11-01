// _FlushReceiveBuffer@4 @ rva 0xd35fa (6 B) — FlushReceiveBuffer serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impFlushReceiveBuffer[];
unsigned long __declspec(naked) __stdcall FlushReceiveBuffer(void *a0)
{
    __asm { jmp dword ptr [impFlushReceiveBuffer] }
}
