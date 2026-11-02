/* _G_Line@16 @ 0x96290 (64 B)
   FA: caller cleans the G_ClipLine pushes (cdecl), G_ULine@16 callee-cleans
   (stdcall); our own ret must be c2 10 00 (stdcall @16) -> declare G_Line
   __stdcall so its obj name is the identity _G_Line@16. */
extern char G_ClipLine(int *a, int *b, int *c, int *d);
extern void __stdcall G_ULine(int a, int b, int c, int d);

void __stdcall G_Line(int a, int b, int c, int d)
{
    if (G_ClipLine(&a, &b, &c, &d))
        G_ULine(a, b, c, d);
}