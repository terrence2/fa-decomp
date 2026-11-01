// _joyGetPos@8 @ rva 0xd3312 (6 B) — WINMM import pass-through thunk; args
// already on the caller stack, so a bare jmp forwards them (real joyGetPos
// reads [esp+4]/[esp+8] and rets 8 straight through the thunk).
extern void *impJoyGetPos[];
unsigned long __declspec(naked) __stdcall joyGetPos(void *a, void *b)
{
    __asm { jmp dword ptr [impJoyGetPos] }
}
