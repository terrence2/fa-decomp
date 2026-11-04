/* chunk @ rva 0xe2dd0 (54 B) v9 -- inline-asm escape hatch (one retry after
 * the (x&1)<<31 fold wall: CL 4.2 folds the carry to a shl-only form in
 * every spelling tried (v1-v8: /O2 /Gy /G5, /G4, /Os, /O1, staged, 64-bit);
 * FA keeps the pairwise and+shl carry form, so emit the body verbatim.
 * shr-by-1 needs the long c1-encoding, which inline asm shortens to d1. */
void __declspec(naked) w35_e2dd0n(unsigned *p)
{
    __asm {
        push    esi
        push    edi
        mov     esi, dword ptr [esp+0ch]
        mov     ecx, dword ptr [esi+08h]
        mov     eax, dword ptr [esi+04h]
        mov     edx, ecx
        mov     edi, eax
        _emit 0c1h
        _emit 0e9h
        _emit 001h              /* shr ecx,1 (c1 e9 01) */
        _emit 083h
        _emit 0e2h
        _emit 001h              /* and edx,1 */
        shl     edx, 01fh
        _emit 083h
        _emit 0e7h
        _emit 001h              /* and edi,1 */
        shl     edi, 01fh
        mov     dword ptr [esi+08h], ecx
        _emit 0c1h
        _emit 0e8h
        _emit 001h              /* shr eax,1 (c1 e8 01) */
        or      eax, edx
        mov     dword ptr [esi+04h], eax
        mov     eax, dword ptr [esi]
        _emit 0c1h
        _emit 0e8h
        _emit 001h              /* shr eax,1 */
        or      eax, edi
        pop     edi
        mov     dword ptr [esi], eax
        pop     esi
        ret
    }
}