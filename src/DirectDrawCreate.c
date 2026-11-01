// _DirectDrawCreate@12 @ rva 0xd3504 (6 B) — DirectDrawCreate (DDRAW) import pass-through thunk.
extern void *impDirectDrawCreate[];
unsigned long __declspec(naked) __stdcall DirectDrawCreate(void *a0, void *a1, void *a2)
{
    __asm { jmp dword ptr [impDirectDrawCreate] }
}
