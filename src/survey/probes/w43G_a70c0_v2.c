// w43G chunk rva 0xa70c0 (80 B) v2: fastcall (ecx=point struct, edx=pass-through arg2).
// FA schedule: ax=[ecx+2]; si=ax<<5; [esp+4]=si; si=[ecx+0xa]; ax+=si; shl ax,5; [esp+6]=ax;
//   ax=[ecx+6]; push edx (arg2 first!); cx=ax<<5; add ax,si; shl ax,5; [esp+0xc]=cx;
//   lea ecx,[esp+8] (B); [esp+0xe]=ax; push ecx; call _BoundsAnd@8; pop esi; add esp,8; ret.
// v2: compute B words in FA's order with the call spelled (B, x) so arg2 (x) materializes first.
extern long __stdcall BoundsAnd(void *b, void *x);

typedef unsigned short us;

long __fastcall w43G_a70c0_q(void *s, void *x)
{
    us B[4];

    B[0] = *(us *)((char *)s + 2) << 5;
    B[1] = (*(us *)((char *)s + 2) + *(us *)((char *)s + 0xa)) << 5;
    B[2] = *(us *)((char *)s + 6) << 5;
    B[3] = (*(us *)((char *)s + 6) + *(us *)((char *)s + 0xa)) << 5;
    return (long)BoundsAnd(B, x);
}
