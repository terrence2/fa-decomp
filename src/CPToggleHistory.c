// @CPToggleHistory@0 @ rva 0x3d880 — cmp byte [_windowTypes+0x3f0],0 /
//   sete al / mov byte [_windowTypes+0x3f0],al / ret. CL's setcc always
//   allocates cl (then mov [m],cl — 8 B longer than FA's a2 moffs store);
//   probed 7 C formulations (w5_toggle, w6_t1/t3/t6/t14/t15/t21) — none
//   reaches sete al + a2. CL's byte-moffs A2 form fires only when the value
//   physically sits in AL (probe w6_t7: `g2[k]=g1` emits a0/a2), so the
//   byte-exact reproduction uses CL's inline assembler (probe w6_tasm
//   exact). The disp32 addend 0x3f0 rides in the reloc content; symbol
//   _windowTypes is the FA chunk symbol (identity).
extern unsigned char windowTypes[];

void CPToggleHistory(void)
{
    __asm {
        cmp byte ptr [windowTypes+0x3f0], 0
        sete al
        mov byte ptr [windowTypes+0x3f0], al
    }
}
