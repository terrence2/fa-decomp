/* @COLSetAngle@8 v2: plain C fastcall. v2: arg1(ecx)=src, arg2(edx)=dst per
 * FA's esi/edi plan; GRSinCos arg3 = &c (int local; low word is cos —
 * GRSinCos writes a WORD); FA overwrites the slot with dword 0x7fff and
 * divides one term by it. */
void __stdcall GRSinCos(short, short *, short *);

void __fastcall COLSetAngle(short *src, short *dst)
{
    short t, s, cw;
    int c, x, y;
    t = (short)(dst[0] - src[0]);
    GRSinCos(t, &s, (short *)&c);
    cw = (short)c;
    x = (int)src[1] * cw;
    x /= 0x7fff;
    c = 0x7fff;
    x += (int)src[2] * (int)s / c;
    dst[1] = (short)x;
    y = (int)src[2] * cw;
    y /= 0x7fff;
    y -= (int)src[1] * (int)s / 0x7fff;
    dst[2] = (short)y;
}