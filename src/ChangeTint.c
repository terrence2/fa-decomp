// _ChangeTint @ rva 0xaf4f0 — tint++ then abs/&3/abs with ONE reused cdq
//   sign mask (C-forms recompute the mask per abs: d84 double 99, d118/d119
//   sar-based reg choices, d120 labs twice) — __declspec(naked) inline asm
//   (probe d123 exact; CL skips prologue/epilogue so the e9 tail survives).
extern long tint;
extern long __fastcall WRSetTint(long j);

__declspec(naked) void ChangeTint_q(void)
{
    __asm {
        mov  eax, dword ptr [tint]
        inc  eax
        cdq
        xor  eax, edx
        sub  eax, edx
        and  eax, 3
        xor  eax, edx
        sub  eax, edx
        mov  ecx, eax
        jmp  WRSetTint
    }
}
