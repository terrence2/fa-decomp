// w29b C: @G_SPolygon@8 @ rva 0xc4e24 (48 B incl. 3-byte cc*3 gap pad).
// fastcall(eax-less, args ecx/edx). FA body (no FPO / gap chunk):
//   push ebx,esi,edi,ebp (only esi used)
//   mov [_gA],edx ; mov esi,edx ; movzx ecx,cx ; mov [_gB],ecx ;
//   mov byte [_gC],1 ; call SUB1 (=@G_SUPolygon@8+0x4cc) ; jae skip ;
//   call SUB2 (=@G_SUPolygon@8) ; skip: pop ebp,edi,esi,ebx ; ret
// The CF-dependent `jae` after a call is not C-formable (CF carries out of
// SUB1's asm body); plus ebp/ebx saves untouched by any C local plan ->
// naked asm with FA's own sequence verbatim.
extern unsigned int gA;
extern unsigned int gB;
extern unsigned char gC;
extern void sub1q(unsigned int, unsigned int);
extern void sub2q(unsigned int, unsigned int);

void __fastcall G_SPoly_q(int a, int b)
{
    __asm {
        push ebx
        push esi
        push edi
        push ebp
        mov dword ptr [gA], edx
        mov esi, edx
        movzx ecx, cx
        mov dword ptr [gB], ecx
        mov byte ptr [gC], 1
        call sub1q
        jae Lskip
        call sub2q
    Lskip:
        pop ebp
        pop edi
        pop esi
        pop ebx
        ret
    }
}