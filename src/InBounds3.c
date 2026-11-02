// _InBounds3@8 @ rva 0x11bd0 (80 B) — is pt inside the 3-row (min,max) box.
// FA for each of 3 rows i: eax=[box+4i] (8b 01/8b 41 04/8b 41 08);
// sar eax,0x10; cmp WORD PTR [pt+2i],ax (66 39) jg fail; cmp WORD PTR
// [pt+2i+2],ax jl fail (all six jumps share the one fail block);
// mov al,1 / xor al,al (AL-only return); ret 8.
// CL 4.2 plain C movsx-extends every short, emits 3b dword compares and 4
// separate return blocks — unsteerable, naked asm.
__declspec(naked) int __stdcall InBounds3(long *box, short *pt)
{
    __asm {
        mov ecx, [esp+4]
        mov edx, [esp+8]
        mov eax, [ecx]
        sar eax, 10h
        cmp word ptr [edx], ax
        jg fail
        cmp word ptr [edx+2], ax
        jl fail
        mov eax, [ecx+4]
        sar eax, 10h
        cmp word ptr [edx+4], ax
        jg fail
        cmp word ptr [edx+6], ax
        jl fail
        mov eax, [ecx+8]
        sar eax, 10h
        cmp word ptr [edx+8], ax
        jg fail
        cmp word ptr [edx+0ah], ax
        jl fail
        mov al, 1
        ret 8
    fail:
        xor al, al
        ret 8
    }
}
