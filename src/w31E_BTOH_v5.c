// _CTDo_btoh @ rva 0x656b0 = 415408, 80 B. v5: naked inline-asm transcript.
// Plain-C v1-v4 (both short and unsigned short locals) compile the v load as
// `66 8b 0d` into CX and the sub with modrm 0d; FA uses the moffs form
// `66 a1` (v in AX) and `66 29 05` (sub word mem,ax) - CL 4.2 has no C
// spelling that steers the 16-bit local to AX here, so transcribe.
extern unsigned char _btohGate;   /* _serviceTicks+0xec */
extern short _btohTF1, _btohTF2;  /* both _curThing+0x1f (fold-defeat pair) */
extern unsigned short _btohTT;    /* _curThing+0x21 */
extern short _btohTL, _btohTL2;   /* both _curThing+0x1d (reload-force pair) */
extern short _btohTD;             /* _curThing+0x23 */

void __declspec(naked) CTDo_btoh(void)
{
    __asm {
        mov al, BYTE PTR [_btohGate]
        test al, al
        jne Lret
        cmp word ptr [_btohTF1], 3e90h
        jge Lbody
        cmp word ptr [_btohTF2], 0c170h
        jg Lret
Lbody:
        mov ax, WORD PTR [_btohTT]
        mov WORD PTR [_btohTT], 0
        sub word ptr [_btohTL], ax
        mov cx, [_btohTL2]
        mov word ptr [_btohTD], cx
Lret:
        ret
    }
}