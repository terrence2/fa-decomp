/* w31A round 1: atan2 (rva 826287 dec, 0xc9baf, 53 B) — naked-asm single
 * retry. Calls FA fixed-point asin (0xc9b0f) / acos (0xc9b64); map TOs are
 * the exact layout chunk names. Callees spelled with Z to keep the obj
 * externals away from any CRT lib def.
 */
extern int asinZ(void);
extern int acosZ(void);

int __declspec(naked) __cdecl atan2Z(void)
{
    __asm {
        cmp ax, 0x5a82
        jg  LB
        cmp ax, 0xa57e
        jl  LB
        push bx
        call asinZ
        pop ax
        or  ax, ax
        jns LA
        sub cx, 0x8000
        neg cx
LA:     ret
LB:     cwd
        push dx
        call acosZ
        pop dx
        xor cx, dx
        sub cx, dx
        ret
    }
}