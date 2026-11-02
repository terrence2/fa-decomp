// @MAPUpdateWPPtrs@8 @ rva 0x221bf (76 B) — fastcall(owner=ecx, wp=edx),
// FPO params=0. Naked-asm escape: FA's register plan (i strictly 16-bit in
// bx with an interleaved mov bx,1 inside the push prolog, owner=esi,
// wp=edi, obj transient in ecx, mem-first cmp word[_nextObjId],bx, call arg
// edx=edi) plus the and-sib objPtrs index are not reachable from plain C
// (probe w21a gave push ebp + 32/16-bit mixed copies for every plain-C
// spelling tried).
extern unsigned short nextObjId;   /* _nextObjId FA.SMS identity */
extern void *objPtrs[];            /* _objPtrs FA.SMS identity */
extern void __fastcall MAPUpdateWPPtrQ(void *o, unsigned long w);
                                    /* @MAPUpdateWPPtrQ@8 -> $FA$_t_42220b */

void __declspec(naked) __fastcall MAPUpdateWPPtrs(void)
{
    __asm {
        push    ebx
        push    esi
        mov     bx, 1
        push    edi
        cmp     nextObjId, bx
        mov     edi, edx
        mov     esi, ecx
        jbe     short done
scan:
        movzx   eax, bx
        mov     ecx, objPtrs[eax*4]
        test    byte ptr [ecx+1], 1
        je      short step
        mov     al, [ecx]
        cmp     al, 2
        je      short hit
        cmp     al, 4
        jne     short step
hit:
        cmp     dword ptr [ecx+0xe4], esi
        jne     short step
        mov     edx, edi
        call    MAPUpdateWPPtrQ
step:
        inc     bx
        cmp     nextObjId, bx
        ja      short scan
done:
        pop     edi
        pop     esi
        pop     ebx
        ret
    }
}