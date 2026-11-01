// @G_UPointFlip@8 @ rva 0x966c0 — G_PointFlip against @G_UPoint@8 (probe d82).
extern char *cb;
extern int __fastcall G_UPoint(int a, int b);

int __fastcall G_UPointFlip_q(int a, int b)
{
    long t = (long)cb;
    int v = *(long *)(t + 6) - b;
    return G_UPoint(a, v - 1);
}
