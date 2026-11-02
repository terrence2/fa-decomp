/* t3_carefuldiv_v5.c — C shell + inline __asm block (the realistic shape
 * of the ORIGINAL Microsoft-style source: C prologue/branch/tail, inline
 * asm for the x87 status classification, quotient kept in st(0) across
 * the integer flag store and the fxam/fstsw read).
 *
 * Target FA order (rva 0xb5130): test den bits / jne+0x0a / [fld real_1;
 * mov esp,ebp; pop ebp; ret] / push eax; fld num; fld den; fdivp;
 * mov g_divFlag,0; fxam; xor eax,eax; fstsw ax; fstp g_divRes; and ...
 * nibble index; cmp g_divCls[eax],0; je+12; mov g_divFlag,1; fldz;
 * fstp g_divRes; pop eax; fld g_divRes; mov eax,[ebp+8]; fstp [eax];
 * fild g_divFlag; mov esp,ebp; pop ebp; ret.
 *
 * Open questions this probe answers:
 *   (1) with an inline __asm block present, does CL still emit the EAGER
 *       den-bit load (mov eax,[esp+0x10]) and does it land between
 *       push ebp and mov ebp,esp (FA's split prologue)?
 *   (2) does CL reserve a 4-B frame slot (sub esp,4) and what for?
 *   (3) does the tail come out 8b 45 08 / d9 18 / db 05?
 */
extern double g_divRes;
extern int g_divFlag;
extern int g_divCls;

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