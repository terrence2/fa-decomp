// _BytesInReceiveBuffer@4 @ rva 0xd362a (6 B) — BytesInReceiveBuffer serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impBytesInReceiveBuffer[];
unsigned long __declspec(naked) __stdcall BytesInReceiveBuffer(void *a0)
{
    __asm { jmp dword ptr [impBytesInReceiveBuffer] }
}
