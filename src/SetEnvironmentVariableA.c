// _SetEnvironmentVariableA@8 @ rva 0xe4dba (6 B) — SetEnvironmentVariableA (KERNEL32) import pass-through thunk.
extern void *impSetEnvironmentVariableA[];
unsigned long __declspec(naked) __stdcall SetEnvironmentVariableA(void *a0, void *a1)
{
    __asm { jmp dword ptr [impSetEnvironmentVariableA] }
}
