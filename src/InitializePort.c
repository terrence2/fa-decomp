// _InitializePort@36 @ rva 0xd361e (6 B) — InitializePort serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impInitializePort[];
unsigned long __declspec(naked) __stdcall InitializePort(void *a0, void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8)
{
    __asm { jmp dword ptr [impInitializePort] }
}
