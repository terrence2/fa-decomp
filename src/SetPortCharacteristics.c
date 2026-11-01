// _SetPortCharacteristics@24 @ rva 0xd3618 (6 B) — SetPortCharacteristics serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impSetPortCharacteristics[];
unsigned long __declspec(naked) __stdcall SetPortCharacteristics(void *a0, void *a1, void *a2, void *a3, void *a4, void *a5)
{
    __asm { jmp dword ptr [impSetPortCharacteristics] }
}
