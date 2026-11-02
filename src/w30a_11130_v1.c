/* $FA$_t_411130 @ rva 0x11130 (dec 69936), 32 B. FA bytes:
 *   33 c0                xor eax,eax
 *   8a c1                mov al,cl
 *   8b 04 85 28 8a 4e 00 mov eax,[eax*4 + _structuralFail2String+0x18]
 *   85 c0                test eax,eax
 *   74 06                je +6
 *   50                   push eax
 *   e8 ..                call _HUDMessage@4
 *   c3                   ret
 * cl comes in from the entry context (caller hand-off), plain ret —
 * no C decl can own cl without a ret-imm mismatch: naked-asm escape.
 */
extern char *structuralFail2String[];   /* =?structuralFail2String@@3PADA */
extern void __stdcall HUDMessage(char *s);   /* =_HUDMessage@4 */

void __declspec(naked) w30a_11130(void)
{
    __asm {
        xor eax, eax
        mov al, cl
        mov eax, structuralFail2String[eax*4 + 0x18]
        test eax, eax
        je L1
        push eax
        call HUDMessage
L1:
        ret
    }
}