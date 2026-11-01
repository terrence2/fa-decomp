/* carefulDiv — pilot 5 (chunk @ rva 0xb5130, size 0x80, NO FPO record).
 *
 * The chunk splits its own prologue (push ebp / mov eax,[esp+0x10] /
 * mov ebp,esp / sub esp,4) — unreachable by normal C statement placement,
 * and there is no FPO entry, so the original is almost certainly a
 * __declspec(naked) function with the whole body in inline asm (fxam also
 * has no C construct). Body = FA's own instruction sequence verbatim:
 *   den == ±0 → return 1.0 (double const @ .rdata 0x4e54f0);
 *   else *out = (float)((double)num/den), zeroed + flagged 1 when the
 *   g_divCls[] classification table flags the quotient; returns the flag.
 *
 * Maps (swap.json): _real_1 = $FA$rdata0+0x49c; _g_divRes/+flag live in the
 * BSS chunk ?palColorRGB@@3UT_RGB@@A (+0x440 / +0x44c); _g_divCls follows
 * float ?rFloor@@3MA (+4).
 */
extern int real_1;        /* the 1.0 const @ .rdata VA 0x4e54f0 (asm-mem) */
extern int g_divCls;      /* classification table base @ VA 0x508270     */
extern double g_divRes;   /* quotient storage @ VA 0x57b958              */
extern int g_divFlag;     /* "division was special" flag @ VA 0x57b964   */

double __declspec(naked) __cdecl carefulDiv(float* out, float num,
                                            float den)
{
    __asm {
        push  ebp
        mov   eax, [esp+0x10]           ; den bits
        mov   ebp, esp
        sub   esp, 4
        test  eax, 0x7fffffff
        jne   L_cd_div
        fld   qword ptr real_1          ; den == ±0 → return 1.0
        mov   esp, ebp
        pop   ebp
        ret
L_cd_div:
        push  eax
        fld   dword ptr [ebp+0xc]       ; num
        fld   dword ptr [ebp+0x10]      ; den
        fdivp st(1), st                 ; st0 = num / den
        mov   dword ptr g_divFlag, 0
        fxam
        xor   eax, eax
        fstsw ax
        fstp  qword ptr g_divRes
        and   eax, 0x4700
        shr   eax, 6
        shl   ah, 5
        or    al, ah
        xor   ah, ah
        cmp   dword ptr g_divCls[eax], 0
        je    L_cd_done
        mov   dword ptr g_divFlag, 1
        fldz
        fstp  qword ptr g_divRes
L_cd_done:
        pop   eax
        fld   qword ptr g_divRes
        mov   eax, [ebp+8]
        fstp  dword ptr [eax]
        fild  dword ptr g_divFlag
        mov   esp, ebp
        pop   ebp
        ret
    }
}