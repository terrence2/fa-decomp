// _LimitAngle@12 @ rva 0x12b30 = 76560, 80 B (stdcall 3 dwords, pushes
// ebx/esi/edi; si = p1 word read BETWEEN push esi and push edi, edi = p2 ptr,
// bx = [p2] word, bx -= si; ecx = ebx; call @Abs@4; cx = p3 word; movsx edx,cx;
// cmp eax,edx; jle -> shared epilogue (p3 plimit: |diff| <= plimit => done);
// test bx,bx; jl -> sub si,cx; else add si,cx; mov [edi],si)
extern int __fastcall AbsSlewQ(int v);
/* map @AbsSlewQ@4=@Abs@4 */

void __stdcall w25c_LimitAngle_q(unsigned int val, unsigned short *angle,
                                 unsigned int plimit)
{
    unsigned short v = (unsigned short)val;
    unsigned short d = (unsigned short)(*angle - v);
    unsigned short pl = (unsigned short)plimit;
    if ((int)(long)AbsSlewQ(d) <= (int)(short)pl)
        return;
    if ((short)d >= 0)
        *angle = (unsigned short)(v + pl);
    else
        *angle = (unsigned short)(v - pl);
}