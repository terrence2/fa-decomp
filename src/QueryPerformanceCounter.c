// _QueryPerformanceCounter@4 @ rva 0xd33d8 (6 B) — KERNEL32 import pass-through thunk.
extern void *impQueryPerformanceCounter[];
unsigned long __declspec(naked) __stdcall QueryPerformanceCounter(void *a)
{
    __asm { jmp dword ptr [impQueryPerformanceCounter] }
}
