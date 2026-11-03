// sincos @ rva 0xc9938 (62 B, no pad) -- FA asm (register-ABI helper,
// args/results in eax/ebx/ebp from callers):
//   movzx ebx,bx / xor ecx,ecx / mov cl,bl / sar ebx,8 / xor bh,bh /
//   add ebx,ebx / movsx ebp,[ebx+sin_table] / movsx eax,[ebx+sin_table+2]
//   / sub eax,ebp / imul ecx / sar eax,8 / add eax,ebp (sin lerp) /
//   movsx ebp,[ebx+cos_table] / movsx ebx,[ebx+cos_table+2] / sub ebx,ebp
//   / imul ebx,ecx / sar ebx,8 / add ebx,ebp (cos lerp) / ret.
// Naked-asm escape.  CL drops the `[ebx+symbol]` base and emits an 8-B
// movsx form for all four table reads (wave-31 base-drop wall): v2 patches
// each 8-B movsx into FA's 7-B `[ebx+disp32]` form with a DIR32 newsite at
// the disp byte; the +2 sites carry payload = FA_imm - symVA (addend class).
extern short in_table[];
extern short cos_table[];

void __declspec(naked) sincos(void)
{
    __asm {
        movzx ebx, bx
        xor ecx, ecx
        mov cl, bl
        sar ebx, 8
        xor bh, bh
        add ebx, ebx
        movsx ebp, word ptr [ebx + in_table]
        movsx eax, word ptr [ebx + in_table + 2]
        sub eax, ebp
        imul ecx
        sar eax, 8
        add eax, ebp
        movsx ebp, word ptr [ebx + cos_table]
        movsx ebx, word ptr [ebx + cos_table + 2]
        sub ebx, ebp
        imul ebx, ecx
        sar ebx, 8
        add ebx, ebp
        ret
    }
}