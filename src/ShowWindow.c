// _ShowWindow@8 @ rva 0xd3492 (6 B) — USER32 import pass-through thunk.
extern void *impShowWindow[];
unsigned long __declspec(naked) __stdcall ShowWindow(void *a, void *b)
{
    __asm { jmp dword ptr [impShowWindow] }
}
