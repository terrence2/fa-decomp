// __cropzeros @ rva 0xd9470 (889968) — naked asm: FA's 89B listing
// verbatim. C (v1-v3) can't reach FA's rotated loops (back-edge
// cmp [edx],0 — CL look-aheads via a register), the [mem],direct
// compares (CL materializes 8a0x/3a) or the dec-then-cmp strip loop, and
// the 89B chunk has no filler so the net length must come out of C — asm
// fixes all three walls.
extern char dotByte;                         /* _dotByte -> __ctype+0x208 */

__declspec(naked) void __cdecl cropzerosq(char *buf)
{
    __asm {
        mov   edx, [esp+0x4]
        cmp   byte ptr [edx], 0
        je    Lcz1
Lcz0:
        mov   al, dotByte
        cmp   byte ptr [edx], al
        je    Lcz1
        inc   edx
        cmp   byte ptr [edx], 0
        jne   Lcz0
Lcz1:
        mov   eax, edx
        inc   edx
        cmp   byte ptr [eax], 0
        je    Lczret
        cmp   byte ptr [edx], 0
        je    Lcz2
Lczs:
        mov   al, byte ptr [edx]
        cmp   al, 0x65
        je    Lcz2
        cmp   al, 0x45
        je    Lcz2
        inc   edx
        cmp   byte ptr [edx], 0
        jne   Lczs
Lcz2:
        mov   eax, edx
        dec   edx
        cmp   byte ptr [edx], 0x30
        jne   Lcz3
Lczs2:
        dec   edx
        cmp   byte ptr [edx], 0x30
        je    Lczs2
Lcz3:
        mov   cl, dotByte
        cmp   byte ptr [edx], cl
        jne   Lcz4
        dec   edx
Lcz4:
        mov   cl, byte ptr [eax]
        inc   edx
        inc   eax
        mov   byte ptr [edx], cl
        test  cl, cl
        jne   Lcz4
Lczret:
        ret
    }
}