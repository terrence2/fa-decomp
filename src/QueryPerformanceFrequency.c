// _QueryPerformanceFrequency@4 @ rva 0xd33de (6 B) — KERNEL32 import pass-through thunk.
extern void *impQueryPerformanceFrequency[];
unsigned long __declspec(naked) __stdcall QueryPerformanceFrequency(void *a)
{
    __asm { jmp dword ptr [impQueryPerformanceFrequency] }
}
