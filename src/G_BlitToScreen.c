// 0xb4340 _G_BlitToScreen@16 (64 B) — v1
extern char *__fastcall MMAccessWq(long h);
extern void __stdcall G_BlitQ(long a1, char *cb, long z1, long z2, char *p,
                              long a3, long a4, long f2, long f6);
extern char *cbW27;

void __stdcall G_BlitToScreenQ(long a1, long a2, long a3, long a4)
{
    char *p;

    p = MMAccessWq(a2);
    G_BlitQ(a1, p, 0, 0, cbW27, a3, a4,
            *(long *)(p + 2), *(long *)(p + 6));
}