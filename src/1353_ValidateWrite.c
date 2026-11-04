// ?_ValidateWrite@@YAHPAXI@Z @ rva 0xdf4a0 (32 B) — int _ValidateWrite
// (void *p, unsigned int cb): return !IsBadWritePtr(p, cb). Byte-identical
// twin of _ValidateRead (esi-held result across the ff 15 IAT call to
// __imp__IsBadWritePtr). Naked asm escape.
extern void *impIsBadWritePtr[];     /* __imp__IsBadWritePtr IAT slot */

int __declspec(naked) __cdecl _ValidateWriteQ(void)
{
    __asm {
        mov  eax, dword ptr [esp+0x8]
        push esi
        mov  esi, 1
        push eax
        mov  ecx, dword ptr [esp+0xc]
        push ecx
        call dword ptr [impIsBadWritePtr]
        test eax, eax
        je   short ok
        xor  esi, esi
    ok:
        mov  eax, esi
        pop  esi
        ret
    }
}