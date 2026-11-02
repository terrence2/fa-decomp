/* $FA$_t_484ac0 @ rva 0x84ac0 (dec 543424), 16 B. FA bytes:
 *   e9 0b 00 00 00   jmp $FA$_t_484ad0   (x87 timer-reset helper)
 *   8d 64 24 00 8d a4 24 00 00 00 00   (census pad, fitobj tail)
 * Pure tail-jmp thunk; no refs (dead chunk) — naked-asm escape, C form
 * unreachable (no ABI/prologue to hang codegen on).
 */
extern void w30a_fwdad0(void);   /* =$FA$_t_484ad0 */

void __declspec(naked) w30a_84ac0(void)
{
    __asm {
        jmp w30a_fwdad0
    }
}