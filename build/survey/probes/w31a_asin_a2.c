/* w31A round 2: asin (rva 826127 dec, 0xc9b0f, 65 B) — naked-asm retry.
 * a1 finding: CL 4.2 inline assembler DROPS the register base of
 * [ebx + symbol] memory operands (emits baseless [disp32]: 66 8b 2d /
 * 66 a1). Fix: _emit the two 66 8b ab / 66 8b 83 disp32 instructions
 * raw with zeroed addend dwords; the round-2 patches (0-length inserts)
 * attach the DIR32 sites at 0x1c / 0x23; the maps carry the deltas
 * (+0x202 / +0x204, FA imm bytes 0x00511582 / 0x00511584; cos_table
 * va 0x511380).
 * Everything else byte-verbatim (cwd emits 66 99 correctly; 16-bit
 * register ops get the 66 prefix; imul cx = 66 f7 e9; nop = tail).
 */
int __declspec(naked) __cdecl asinZ(void)
{
    __asm {
        cwd
        xor ax, dx
        sub ax, dx
        push dx
        mov bl, ah
        xor bh, bh
        mov cx, ax
        xor ch, ch
        shl bx, 1
        movzx ebx, bx
        _emit 0x66
        _emit 0x8b
        _emit 0xab
        _emit 0                    ; disp32 addend (map carries +0x202)
        _emit 0
        _emit 0
        _emit 0
        _emit 0x66
        _emit 0x8b
        _emit 0x83
        _emit 0                    ; disp32 addend (map carries +0x204)
        _emit 0
        _emit 0
        _emit 0
        sub ax, bp
        imul cx
        mov al, ah
        mov ah, dl
        add ax, bp
        mov cx, ax
        pop dx
        xor cx, dx
        sub cx, dx
        ret
        nop
    }
}