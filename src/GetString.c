// _GetString@12 @ rva 0xd3666 (6 B) — GetString serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impGetString[];
unsigned long __declspec(naked) __stdcall GetString(void *a0, void *a1, void *a2)
{
    __asm { jmp dword ptr [impGetString] }
}
