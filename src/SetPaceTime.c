// _SetPaceTime@8 @ rva 0xd3606 (6 B) — SetPaceTime serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impSetPaceTime[];
unsigned long __declspec(naked) __stdcall SetPaceTime(void *a0, void *a1)
{
    __asm { jmp dword ptr [impSetPaceTime] }
}
