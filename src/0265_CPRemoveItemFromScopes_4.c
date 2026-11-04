// @CPRemoveItemFromScopes@4 @ rva 0x3e200 (48 B) — FA asm: ba <targetV+
//   0x1c30>/66 8b f1/b9 <targetV+0xd8>/56/e8 (helper call)/56/ba <ifmHandle+
//   0x1c2c>/b9 <ifmHandle+0xd4>/e8/c3.  Inline-asm escape: FA builds the
//   fastcall helper args with imm32 (ba/b9) movs, not CL's lea forms, and
//   reuses esi across the two calls with the fastcall param copied via
//   66 8b f1 — no plain-C reg plan reaches this.
//   Probe build/w4probe/b17_cpris_v2.c — exact modulo fixup dwords.

extern char targetV[];
extern char ifmHandle[];

void __fastcall cpRmItemScopeHelper(long base, long end, unsigned short id);

void __fastcall CPRemoveItemFromScopes(unsigned short id) {
    __asm {
        mov edx, offset targetV + 0x1c30
        mov si, cx
        mov ecx, offset targetV + 0xd8
        push esi
        call cpRmItemScopeHelper
        push esi
        mov edx, offset ifmHandle + 0x1c2c
        mov ecx, offset ifmHandle + 0xd4
        call cpRmItemScopeHelper
    }
}