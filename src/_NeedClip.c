// _NeedClip @ rva 0xd0c24 (20 B, gap chunk) — copies the clip flag byte
// (normal_table+0xb0) into gouraudOn+0x11d (a0 load / a2 store, MASM's
// direct moffs AL forms — addends live only in the maps, wave-12 rule),
// zeroes eax and tail-calls check_flat+0x2d0 which takes the flag in AL
// (C-unrepresentable) then returns. RestoreClip family (wave 17).
extern char needClipSrc[];
extern char gouraudOn[];
extern void needClipCallee(void);

void __declspec(naked) NeedClip(void)
{
    __asm {
        mov  al, byte ptr needClipSrc
        mov  byte ptr gouraudOn, al
        xor  eax, eax
        call needClipCallee
        ret
    }
}