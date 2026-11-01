// _Dial@12 @ rva 0xd367e (6 B) — Dial serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impDial[];
unsigned long __declspec(naked) __stdcall Dial(void *a0, void *a1, void *a2)
{
    __asm { jmp dword ptr [impDial] }
}
