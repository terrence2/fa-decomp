extern unsigned int gA;
extern unsigned int gB;
extern unsigned char gC;
extern void sub1q(unsigned int, unsigned int);
extern void sub2q(unsigned int, unsigned int);

void __declspec(naked) __fastcall G_SPoly_q(int a, int b)
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