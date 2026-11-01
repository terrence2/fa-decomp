// _UnInitializePort@4 @ rva 0xd3612 (6 B) — UnInitializePort serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impUnInitializePort[];
unsigned long __declspec(naked) __stdcall UnInitializePort(void *a0)
{
    __asm { jmp dword ptr [impUnInitializePort] }
}
