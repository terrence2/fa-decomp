// _BytesInTransmitBuffer@4 @ rva 0xd3630 (6 B) — BytesInTransmitBuffer serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impBytesInTransmitBuffer[];
unsigned long __declspec(naked) __stdcall BytesInTransmitBuffer(void *a0)
{
    __asm { jmp dword ptr [impBytesInTransmitBuffer] }
}
