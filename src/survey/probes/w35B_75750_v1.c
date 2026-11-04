/* w35B: _LimitFromLowSpeed@12 @ rva 0x75750 (112 B)
 * FA (frame ebp, no ebp frame — 4 reg pushes only):
 *   ecx=[esp+4] (a); edi=[esp+0x18] (d=p3); eax=[ecx] (*a); esi=[esp+0x18]
 *   (b=p2); *a-=d; *b-=d;
 *   eax=moffs ct34 (curThing+0x34); sar 8; cdq; xor edx; ebp=100; sub edx
 *     (trunc-div by 256);
 *   edx=oneGStallSpeed (8b 15); ebx=eax(L);
 *   eax=lea 5x; lea 25x; shl 3 (=200*stall); cdq; idiv ebp(100);  <-- idiv
 *   cmp eax,ebx; ebp=eax; jle skip (if 2*stall/100 > L): *a=a*L/ebp;
 *   *b=b*L/ebp;
 *   skip: eax=*a (pop ebp between!); *a+=d; ecx=*b; *b+=d (ecp interleaved);
 *   ret 0xc.
 * CL 4.2 magic-multiplies a /100 const => idiv is MASM-only -> naked asm v1.
 */
extern void lim_ct34(void); /* unused */
extern char ct34[];         /* _curThing+0x34 */
extern long oneGStallSpeed; /* ?oneGStallSpeed@@3JA */

void __declspec(naked) __stdcall LimitFromLowSpeed(void)
{
    __asm {
        mov     ecx, [esp+4]
        push    ebx
        push    esi
        push    edi
        mov     edi, [esp+18h]
        push    ebp
        mov     eax, [ecx]
        mov     esi, [esp+18h]
        sub     eax, edi
        mov     [ecx], eax
        sub     [esi], edi
        mov     eax, dword ptr [ct34]
        sar     eax, 8
        cdq
        xor     eax, edx
        mov     ebp, 64h
        sub     eax, edx
        mov     edx, dword ptr [oneGStallSpeed]
        mov     ebx, eax
        lea     eax, [edx+edx*4]
        lea     eax, [eax+eax*4]
        shl     eax, 3
        cdq
        idiv    ebp
        cmp     eax, ebx
        mov     ebp, eax
        jle     Lskip
        mov     eax, [ecx]
        imul    eax, ebx
        cdq
        idiv    ebp
        mov     [ecx], eax
        mov     eax, [esi]
        imul    eax, ebx
        cdq
        idiv    ebp
        mov     [esi], eax
    Lskip:
        mov     eax, [ecx]
        pop     ebp
        add     eax, edi
        mov     [ecx], eax
        mov     ecx, [esi]
        add     ecx, edi
        pop     edi
        mov     [esi], ecx
        pop     esi
        pop     ebx
        ret     0ch
    }
}