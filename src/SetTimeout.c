// _SetTimeout@8 @ rva 0xd360c (6 B) — SetTimeout serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impSetTimeout[];
unsigned long __declspec(naked) __stdcall SetTimeout(void *a0, void *a1)
{
    __asm { jmp dword ptr [impSetTimeout] }
}
