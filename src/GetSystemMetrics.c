// _GetSystemMetrics@4 @ rva 0xd34da (6 B) — USER32 import pass-through thunk.
extern void *impGetSystemMetrics[];
unsigned long __declspec(naked) __stdcall GetSystemMetrics(void *a)
{
    __asm { jmp dword ptr [impGetSystemMetrics] }
}
