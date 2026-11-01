// _joyGetDevCapsA@12 @ rva 0xd3318 (6 B) — WINMM import pass-through thunk.
extern void *impJoyGetDevCapsA[];
unsigned long __declspec(naked) __stdcall joyGetDevCapsA(void *a, void *b, unsigned c)
{
    __asm { jmp dword ptr [impJoyGetDevCapsA] }
}
