// _joyGetPosEx@8 @ rva 0xd3324 (6 B) — WINMM import pass-through thunk.
extern void *impJoyGetPosEx[];
unsigned long __declspec(naked) __stdcall joyGetPosEx(void *a, void *b)
{
    __asm { jmp dword ptr [impJoyGetPosEx] }
}
