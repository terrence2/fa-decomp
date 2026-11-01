// _PostQuitMessage@4 @ rva 0xd34c2 (6 B) — USER32 import pass-through thunk.
extern void *impPostQuitMessage[];
unsigned long __declspec(naked) __stdcall PostQuitMessage(void *a)
{
    __asm { jmp dword ptr [impPostQuitMessage] }
}
