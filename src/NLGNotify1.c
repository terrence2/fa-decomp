// __NLG_Notify1 @ rva 0xd495d (9 B, gap chunk — no FPO record) — save
// ebx/ecx, point ebx at __NLG_Destination (0x51a050, identity data extern),
// eb 0a SHORT jmp into __NLG_Notify+0xa (0x4d4970). Same _emit short-jmp
// escape as _NLG_Return2 (MASM e9 would add 3 B), probe w16b_7b exact.
extern long _NLG_Destination;

void __declspec(naked) _NLG_Notify1(void)
{
    __asm {
        push ebx
        push ecx
        mov  ebx, OFFSET _NLG_Destination
        _emit 0xeb          ; jmp short __NLG_Notify+0xa (0x4d4970)
        _emit 0x0a          ; rel8 = +0xa
    }
}