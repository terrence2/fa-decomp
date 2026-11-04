/* acos @ rva 826212 dec (0xc9b64, 75 B, gap chunk, no FPO) — fixed-point
 * trig in the 8086-remnant band; sibling of w31a_asin_a2 (same recipe:
 * naked __cdecl, byte-exact bands, the two [ebx + cos_table] lookups
 * _emit'd raw because CL 4.2 inline-asm drops the register base of
 * [reg + symbol] operands). DIR32 newsites (0-length inserts) attach at
 * the disp dwords chunk 0x1f / 0x26; maps carry deltas +0x304 / +0x306
 * (FA imm bytes 0x00511684 / 0x00511686; cos_table va 0x511380).
 * Section name = chunk "acos" defines the public that GRACos/atan2's
 * maps reference. Everything else byte-verbatim: cwd emits 66 99; 16-bit
 * reg ops get the 66 prefix; imul cx = 66 f7 e9; xor reg,reg emits 32 xx. */
void __declspec(naked) __cdecl acosZ(void)
{
    __asm {
        mov ax, bx
        cwd
        xor ax, dx
        sub ax, dx
        push dx
        mov cx, ax
        xor ch, ch
        mov bl, ah
        xor bh, bh
        shl bx, 1
        movzx ebx, bx
        _emit 0x66
        _emit 0x8b
        _emit 0xab
        _emit 0                    ; disp32 (map carries +0x304)
        _emit 0
        _emit 0
        _emit 0
        _emit 0x66
        _emit 0x8b
        _emit 0x83
        _emit 0                    ; disp32 (map carries +0x306)
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
        and dx, 0x8000
        add cx, dx
        ret
    }
}