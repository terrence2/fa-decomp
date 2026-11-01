// _PeekChar@4 @ rva 0xd363c (6 B) — PeekChar serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impPeekChar[];
unsigned long __declspec(naked) __stdcall PeekChar(void *a0)
{
    __asm { jmp dword ptr [impPeekChar] }
}
