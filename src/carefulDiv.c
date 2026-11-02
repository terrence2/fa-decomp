/* carefulDiv — t3_carefuldiv_v5 (chunk @ rva 0xb5130 = 741680 decimal,
 * size 0x80, NO FPO record). C shell + ONE inline __asm block: the
 * realistic shape of the original Microsoft-style source.
 *
 * NEW idiom (disproves the old "split prologue is unreachable" note):
 * with an inline __asm block present, CL 4.2 (a) forces a push-ebp frame
 * with no FPO record (FA's exact frame style) and (b) STILL emits the /O2
 * eager parameter load (mov eax,[esp+0x10]) BETWEEN push ebp and
 * mov ebp,esp — FA's split prologue. Plain C never chooses this form: with
 * no asm it uses an esp-only frame (no push ebp) or adjacent
 * push ebp/mov ebp,esp. The x87 fxam/fstsw status-nibble classification
 * core has no CL 4.2 intrinsic — that part stays an asm block; everything
 * else (prologue, eager load, den-bit test a9 / 75 0a, early return-1.0
 * const block, C tail fld/fstp/fild) is real C. EXACT, zero patches, 0x7b
 * code + census tail 05 00 00 00 00. The 8 FA .reloc HIGHLOW sites decoded
 * match our 8 relocs 0x13/0x26/0x37/0x4c/0x55/0x61/0x68/0x73.
 *
 * Body = FA's order: den == ±0 → return 1.0 ($T95, .rdata const
 * $FA$rdata0+0x49c → VA 0x4e54f0); else *out = (float)((double)num/den),
 * zeroed + flagged 1 when the g_divCls[] table flags the quotient; the
 * quotient stays in st(0) across the flag store + fxam/fstsw read; asm
 * keeps FA's push eax/pop eax scratch pair and the plain-C in-block label
 * resolves to FA's exact je rel8 (74 12); inline asm auto-9b WAIT before
 * fstsw matches FA's 9b df e0.
 *
 * Maps (swap.json): '$T95=$FA$rdata0+0x49c' (FROM is CL's internal const
 * symbol $T95, replacing the old _real_1 extern);
 * '_g_divFlag=?palColorRGB@@3UT_RGB@@A+0x44c',
 * '_g_divRes=?palColorRGB@@3UT_RGB@@A+0x440' (BSS in ?palColorRGB@@),
 * '_g_divCls=?rFloor@@3MA+0x4'.
 *
 * Probes: build/survey/probes/t3_carefuldiv_v5.c (EXACT final),
 * v1 (pure C, no asm — 58 B, fdiv m32, esp frame), v2 (statement-order
 * probe: CL's fstp AFTER the flag store matches FA's interleave), v3
 * (ebp force via address-taken local failed — CL kept esp frame),
 * t3_splitpro_v1 (eager load only with esp frame), t3_carefuldiv_cur
 * (verbatim old naked form, byte-EXACT as well).
 */
extern int g_divCls;      /* classification table base @ VA 0x508270     */
extern double g_divRes;   /* quotient storage @ VA 0x57b958              */
extern int g_divFlag;     /* "division was special" flag @ VA 0x57b964   */

double __cdecl carefulDiv(float *out, float num, float den)
{
    unsigned nb = *(unsigned *)&den;
    if ((nb & 0x7fffffffu) == 0u)
        return 1.0;
    __asm {
        push  eax
        fld   dword ptr num
        fld   dword ptr den
        fdivp st(1), st
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
        je    Lcd4done
        mov   dword ptr g_divFlag, 1
        fldz
        fstp  qword ptr g_divRes
Lcd4done:
        pop   eax
    }
    *out = (float)g_divRes;
    return g_divFlag;
}