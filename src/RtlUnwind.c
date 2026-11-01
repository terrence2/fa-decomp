// _RtlUnwind@16 @ rva 0xe4dae (6 B) — RtlUnwind (KERNEL32) import pass-through thunk.
extern void *impRtlUnwind[];
unsigned long __declspec(naked) __stdcall RtlUnwind(void *a0, void *a1, void *a2, void *a3)
{
    __asm { jmp dword ptr [impRtlUnwind] }
}
