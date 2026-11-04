/* _AnglesOffNose@16 @ rva 0x118f0 (112 B) -- v2: pack(1) struct (FA's f11
 * sits at odd +0x11; CL's default alignment pushed it to +0x12); clamp
 * if/else written inverted so CL places the add branch at the jump target
 * (FA polarity: cmp; jg add-target; fall sub; jmp; add). */
#pragma pack(1)
typedef struct {
    char p[0x11];
    short f11;
    char q[0xa];        /* 0x13..0x1c */
    short f1d;
    short f1f;
} STT;
#pragma pack()

extern void __stdcall w37c_angles(short *a, long b, short *c, short *d);
extern long __fastcall w37c_absx(long v);

void __stdcall w37c_aon(STT *st, long p2, short *p3, short *p4)
{
    long x = p2;
    short l[2];

    w37c_angles(&st->f11, x, &l[0], &l[1]);
    l[0] -= st->f1d;
    if (p3)
        *p3 = l[0];
    if (w37c_absx(*(long *)l) <= 0x3ffc)
        l[1] -= st->f1f;
    else
        l[1] += st->f1f;
    if (p4)
        *p4 = l[1];
}