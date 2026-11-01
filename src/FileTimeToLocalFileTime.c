// _FileTimeToLocalFileTime@8 @ rva 0xd340e (6 B) — KERNEL32 import pass-through thunk.
extern void *impFileTimeToLocalFileTime[];
unsigned long __declspec(naked) __stdcall FileTimeToLocalFileTime(void *a, void *b)
{
    __asm { jmp dword ptr [impFileTimeToLocalFileTime] }
}
