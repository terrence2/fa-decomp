// _MSGPop@0 @ rva 0x18490 — 16-bit button counter over ?lastWeaponButton@@3DA:
// fa's 66 a1 / 66 48 / 66 a3 in-reg dec + moffs store-back are asm-only (C folds
// to 66 ff mem-dec); table byte read via movsx'd index (probe w11b_07, byte-exact;
// addends 0xe8 / 0x8 / 0x64c8 baked onto the msgBtnBase base anchor)
extern char msgBtnBase[];
__declspec(naked) void __stdcall MSGPop_q(void)
{
    __asm {
        mov ax, word ptr [msgBtnBase + 0xe8]
        dec ax
        movsx ecx, ax
        mov word ptr [msgBtnBase + 0xe8], ax
        mov al, byte ptr msgBtnBase[ecx+0x64c8]
        mov byte ptr [msgBtnBase + 0x8], al
        ret
    }
}