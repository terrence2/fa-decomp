// __control87 @ rva 0xdf650 (63 B, FPO fpo/esp locals=1 params=2) — CRT
// x87 control-word update: fnstcw the current CW (MASM auto-waits: 9b
// prefix, probe w21_probe1) onto the esp slot, push it, call helper 0
// ($FA$_t_4df6f0: maps new CW bits into FA's 0x100-ish mask space),
// combine: esi = ~(new & ~mask)?? — FA order: ecx = mask & [esp+0xc]
// slot... exact plan: esi = ecx(new), and ecx with the saved CW slot,
// not esi, and esi with helper's eax, or esi with ecx; push esi, call
// helper 1 ($FA$_t_4df7a0), store returned ax 16-bit at [esp+8], fldcw
// it back as the new CW, return esi. Naked asm (x87 + fixed esp-slot
// plan; second 9b placement is FA's own).
extern void *ctrl87fnA(void);
extern void *ctrl87fnB(void);

void __declspec(naked) control87_q(void)
{
    __asm {
        sub  esp, 4
        push esi
        fstcw word ptr [esp+6]
        mov  eax, dword ptr [esp+6]
        push eax
        call ctrl87fnA
        mov  ecx, dword ptr [esp+0x14]
        add  esp, 4
        mov  esi, ecx
        and  ecx, dword ptr [esp+0xc]
        not  esi
        and  esi, eax
        or   esi, ecx
        push esi
        call ctrl87fnB
        mov  word ptr [esp+8], ax
        add  esp, 4
        fldcw word ptr [esp+4]
        mov  eax, esi
        pop  esi
        add  esp, 4
        ret
    }
}