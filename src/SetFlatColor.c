// SetFlatColor @ rva 0xd077c (16 B, gap chunk; 1 B 90 census pad) — pusha,
// pass gouraudOn+0x1 (the current flat-color index word) as the fastcall
// first argument (movzx ecx, word ptr [gouraudOn+1]; @G_SetColor@4 has
// FPO params=0 — the arg travels in ecx, fastcall convention), then
// popa/ret. pusha/popa are asm-only: CL's pusha/popa mnemonics emit
// the 16-bit 66 60/66 61 forms, so the bare 60/61 bytes are baked with
// _emit. The +0x1 field disp is baked in the C (wave-12 double-addend
// rule; map TO is the bare gouraudOn anchor).
extern void __fastcall G_SetColor(int color);
extern char gouraudOn[];

void __declspec(naked) SetFlatColor(void)
{
    __asm {
        _emit 0x60              ; pusha (bare 60 — CL's pusha is 66 60)
        movzx ecx, word ptr [gouraudOn + 1]
        call G_SetColor
        _emit 0x61              ; popa
        ret
    }
}