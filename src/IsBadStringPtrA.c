// _IsBadStringPtrA@8 @ rva 0xd338a (6 B) — KERNEL32 import pass-through thunk.
extern void *impIsBadStringPtrA[];
unsigned long __declspec(naked) __stdcall IsBadStringPtrA(void *a, void *b)
{
    __asm { jmp dword ptr [impIsBadStringPtrA] }
}
