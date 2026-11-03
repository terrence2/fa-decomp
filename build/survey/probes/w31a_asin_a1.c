/* w31A round 1: asin (rva 826127 dec, 0xc9b0f, 65 B) — naked-asm single
 * retry (16-bit fixed-point register ABI is a C wall; this is the one
 * allowed inline-asm escape). Body bytes verbatim vs raw FA.
 * The two DIR32 disp32s resolve via maps: cosT1 -> cos_table+0x202,
 * cosT2 -> cos_table+0x204 (FA imm bytes 0x00511582/0x00511584,
 * cos_table va 0x511380).
 */
extern char cosT1;              /* -> cos_table+0x202 */
extern char cosT2;              /* -> cos_table+0x204 */

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
        mov bp, word ptr [ebx + cosT1]
        mov ax, word ptr [ebx + cosT2]
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