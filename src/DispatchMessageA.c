// _DispatchMessageA@4 @ rva 0xd3498 (6 B) — USER32 import pass-through thunk.
extern void *impDispatchMessageA[];
unsigned long __declspec(naked) __stdcall DispatchMessageA(void *a)
{
    __asm { jmp dword ptr [impDispatchMessageA] }
}
