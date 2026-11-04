// ?_ValidateRead@@YAHPBXI@Z @ rva 0xdf480 (32 B) — int _ValidateRead
// (const void *p, unsigned int cb): return !IsBadReadPtr(p, cb). FA keeps
// the result in esi (mov esi,1 before the IAT call — eax busy carrying cb),
// je-over xor esi,esi, mov eax,esi. IAT call is ff 15 direct
// (__imp__IsBadReadPtr slot, no @N in FA's mkimp name). Naked asm escape
// (esi-held-result plan is not plain-C steerable).
extern void *impIsBadReadPtr[];      /* __imp__IsBadReadPtr IAT slot */

int __declspec(naked) __cdecl _ValidateReadQ(void)
{
    __asm {
        mov  eax, dword ptr [esp+0x8]
        push esi
        mov  esi, 1
        push eax
        mov  ecx, dword ptr [esp+0xc]
        push ecx
        call dword ptr [impIsBadReadPtr]
        test eax, eax
        je   short ok
        xor  esi, esi
    ok:
        mov  eax, esi
        pop  esi
        ret
    }
}