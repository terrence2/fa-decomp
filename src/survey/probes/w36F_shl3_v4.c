/* w36F 0xe2d90 (62B) v4 — naked-asm escape (w35E 0xe2dd0 twin precedent:
 * CL 4.2 folds (x&0x80000000)>>31 to shr-only in every spelling tried
 * (direct, divided, bitfield); FA keeps the pairwise and+shr carry form and
 * the lea [ecx*2+0] double, so the body is emitted verbatim.
 * shr 0x1f keeps the c1 long form (only count-1 shortens to d1).
 * and 0x80000000 uses the imm32 81-form (no imm8 sign-extend exists).
 * lea [ecx*2+0] with no base register forces the disp32 sib (8d 04 4d).
 * FA chunk 62 B = 61 B body + 1 B cc pad (census).
 */
void __declspec(naked) w36f_shl3n(unsigned long *p)
{
    __asm {
        mov     edx, dword ptr [esp+04h]
        push    esi
        push    edi
        mov     eax, dword ptr [edx]
        mov     edi, eax
        mov     ecx, dword ptr [edx+04h]
        and     edi, 80000000h
        mov     esi, ecx
        shr     edi, 01fh
        and     esi, 80000000h
        shr     esi, 01fh
        add     eax, eax
        mov     dword ptr [edx], eax
        lea     eax, dword ptr [ecx*2+0]
        or      eax, edi
        pop     edi
        mov     dword ptr [edx+04h], eax
        mov     eax, dword ptr [edx+08h]
        add     eax, eax
        or      eax, esi
        pop     esi
        mov     dword ptr [edx+08h], eax
        ret
    }
}