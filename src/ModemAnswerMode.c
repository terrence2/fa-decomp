// _ModemAnswerMode@8 @ rva 0xd366c (6 B) — ModemAnswerMode serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impModemAnswerMode[];
unsigned long __declspec(naked) __stdcall ModemAnswerMode(void *a0, void *a1)
{
    __asm { jmp dword ptr [impModemAnswerMode] }
}
