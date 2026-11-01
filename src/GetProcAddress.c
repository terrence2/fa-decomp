// _GetProcAddress@8 @ rva 0xd3426 (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetProcAddress[];
unsigned long __declspec(naked) __stdcall GetProcAddress(void *a, void *b)
{
    __asm { jmp dword ptr [impGetProcAddress] }
}
