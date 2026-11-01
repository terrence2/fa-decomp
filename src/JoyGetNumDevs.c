// _joyGetNumDevs@0 @ rva 0xd331e (6 B) — WINMM import pass-through thunk.
extern void *impJoyGetNumDevs[];
unsigned long __declspec(naked) __stdcall joyGetNumDevs(void)
{
    __asm { jmp dword ptr [impJoyGetNumDevs] }
}
