// sincos @ rva 0xc9938 (62 B, no pad) -- FA asm (register-ABI helper):
//   movzx ebx,bx / xor ecx,ecx / mov cl,bl / sar ebx,8 / xor bh,bh /
//   add ebx,ebx / (tbl1) movsx ebp,word [ebx+sin_table] / sub eax,ebp /
//   imul ecx / sar eax,8 / add eax,ebp / (tbl2) movsx ebp,word
//   [ebx+sin_table+2] / sub ebx,ebp / imul ebx,ecx / sar ebx,8 / add
//   ebx,ebp / ret.  Args/results travel in eax/ebx/ebp from the callers;
//   no prologue -- naked-asm escape.
extern short in_table[];

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
        sub eax, ebp
        imul ecx
        sar eax, 8
        add eax, ebp
        movsx ebp, word ptr [ebx + in_table + 2]
        sub ebx, ebp
        imul ebx, ecx
        sar ebx, 8
        add ebx, ebp
        ret
    }
}