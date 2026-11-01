// ?_ValidateExecute@@YAHP6GHXZ@Z @ rva 0xdf4c0 (27 B) — int
// _ValidateExecute(int (__stdcall *pfn)(void)): r=1 pre-materialized in
// esi (mov esi,1 between the esi save and the arg push), IsBadCodePtr
// through the IAT as ff 15, zero the flag on a bad pointer, return esi.
// Plain C probes added CL's dead push ebx/pop ebx wrap around the
// dllimport call (arg is a memory load — wave-11/17 rule) and pushed the
// arg before mov esi,1 — naked asm escape with an imp-array extern
// (_impIsBadCodePtr=__imp__IsBadCodePtr, IsBadCodePtr-thunk convention).
extern void *impIsBadCodePtr[];

int __declspec(naked) _ValidateExecute(void)
{
    __asm {
        mov  eax, dword ptr [esp+4]     ; pfn (stack arg)
        push esi
        mov  esi, 1                     ; r = 1
        push eax
        call dword ptr [impIsBadCodePtr]
        test eax, eax
        je   Lgood
        xor  esi, esi                   ; r = 0 (bad code ptr)
Lgood:
        mov  eax, esi
        pop  esi
        ret
    }
}