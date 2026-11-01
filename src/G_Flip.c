extern char *cb;
extern void __fastcall G_ReverseVertices(int a, void *b);
void __fastcall G_Flip(int p, void *v)
{
    int n;
    char *e;
    unsigned long w;
    if (p > 0)
    {
        e = (char *)v + 4;
        for (n = p; n != 0; n--)
        {
            w = *(unsigned long *)e;
            *(unsigned long *)e =
                (unsigned long)(((*(long *)(cb + 6) - 1) << 16) - w);
            e += 12;
        }
    }
    G_ReverseVertices(p, v);
}
