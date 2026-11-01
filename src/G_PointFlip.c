// @G_PointFlip@8 @ rva 0x966a0 — tail-jmp @G_Point@8 with edx = cb->f6 - b - 1
//   (probe d68 exact with cb as pointer).
extern char *cb;
extern int __fastcall G_Point(int a, int b);

int __fastcall G_PointFlip_q(int a, int b)
{
    long t = (long)cb;
    int v = *(long *)(t + 6) - b;
    return G_Point(a, v - 1);
}
