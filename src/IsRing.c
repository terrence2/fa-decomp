// _IsRing@4 @ rva 0xd3660 (6 B) — IsRing serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impIsRing[];
unsigned long __declspec(naked) __stdcall IsRing(void *a0)
{
    __asm { jmp dword ptr [impIsRing] }
}
