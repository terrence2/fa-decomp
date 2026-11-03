/* w31A round 1: code_pnt (rva 833056 dec, 0xcb620, 52 B) — naked-asm single
 * retry. Three sign-extended 16-bit register params (bx, cx, bp), shld
 * bit-comb; C cannot name the ABI (wall). Trailing 8b c0 = FA tail pad
 * (census-proven filler), left to fitobj.
 */
int __declspec(naked) __cdecl codePntZ(void)
{
    __asm {
        push esi
        movsx ebx, bx
        movsx ecx, cx
        movsx ebp, bp
        dec ebp
        lea eax, [ebp + 0]
        sar eax, 0x1f
        lea esi, [ecx + ebp * 1]
        shld eax, esi, 1
        mov esi, ebp
        sub esi, ecx
        shld eax, esi, 1
        mov esi, ebp
        sub esi, ebx
        shld eax, esi, 1
        lea esi, [ebx + ebp * 1]
        shld eax, esi, 1
        inc ebp
        pop esi
        ret
    }
}