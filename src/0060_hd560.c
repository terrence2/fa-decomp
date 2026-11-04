/* $FA$_t_40d560 @ rva 0xd560 (dec 54624), 32 B. FA bytes:
 *   66 8b 91 b4 00 00 00   mov dx,[ecx+0xb4]
 *   66 85 d2               test dx,dx
 *   74 05                  je +5
 *   e9 bf 13 00 00         jmp $FA$_t_40e930     (2368 B func: ecx=OBJ*, dx=word)
 *   c3                     ret
 * dx is BOTH the guard value and the forwarded 16-bit arg of the target
 * (target does mov bp,dx) — 16-bit register-ABI forwarding: naked-asm escape.
 */
extern void w30a_e930(void);   /* =$FA$_t_40e930 */

void __declspec(naked) w30a_d560(void)
{
    __asm {
        mov dx, word ptr [ecx+0xb4]
        test dx, dx
        je L1
        jmp w30a_e930
L1:
        ret
    }
}