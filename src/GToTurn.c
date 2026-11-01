// @GToTurn@8 @ rva 0x75970 (64 B) — param1 (cx) clamped to 0x7d, signed ×2500
//   via the push-ebx/lea×5 chain (shl 2 + four lea [r+r*4]), idiv by param2
//   (dx), clamped to [-10000, 10240].  CL 4.2 folds *2500 to its own
//   shift-add decomposition, never this chain (wave-6 @SpeedOfSound@4
//   precedent) — naked asm.
__declspec(naked) int GToTurn_q(void)
{
    __asm {
        push ebx
        cmp edx, 0x7d
        jge L1
        mov edx, 0x7d
    L1:
        movsx eax, cx
        shl eax, 2
        lea ecx, [eax + eax * 4]
        lea ebx, [ecx + ecx * 4]
        lea eax, [ebx + ebx * 4]
        movsx ecx, dx
        lea eax, [eax + eax * 4]
        cdq
        idiv ecx
        cmp eax, 0xffffd800
        jge L2
        mov eax, 0xffffd800
        pop ebx
        ret
    L2:
        cmp eax, 0x2800
        jle L3
        mov eax, 0x2800
    L3:
        pop ebx
        ret
    }
}