/* __allmul @ rva 0xd4d40 (dec 871744), 64 B gap chunk (no FPO) — EXACT,
 * naked-asm escape (CRT hand asm: mul + callee-pops ret 0x10; CL emits
 * __allmul as an intrinsic *call site*, never as this body).
 * The C symbol for `allmul` in .c is ___allmul -> map ___allmul=__allmul.
 */
void __declspec(naked) allmul(void)
{
    __asm {
        mov eax, [esp+8]
        mov ecx, [esp+16]
        or ecx, eax
        mov ecx, [esp+12]
        jne bigpart
        mov eax, [esp+4]
        mul ecx
        ret 16
    bigpart:
        push ebx
        mul ecx
        mov ebx, eax
        mov eax, [esp+8]
        mul dword ptr [esp+20]
        add ebx, eax
        mov eax, [esp+8]
        mul ecx
        add edx, ebx
        pop ebx
        ret 16
    }
}