// @G_SetFullClipBox@0 @ rva 0x95720 — cb is a POINTER global: load it (a1)
//   then read members via [eax+disp] (probe d66 exact; treating cb as an
//   array reads members as direct moffs and diverges — d58).
extern char *cb;
extern void __fastcall G_SetClipBox(int a, int b, int c, int d);

void G_SetFullClipBox_q(void)
{
    long b = (long)cb;
    G_SetClipBox(0, 0, *(long *)(b + 2), *(long *)(b + 6));
}
