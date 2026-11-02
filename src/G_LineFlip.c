// _G_LineFlip@16 @ rva 0x96740 — byte-identical twin of G_ULineFlip
// (0x96710) except the tail call targets _G_Line@16.
extern char* cb;                        /* _cb */
extern void __stdcall G_Line(int a, int b, int c, int d);

void __stdcall G_LineFlip_q(int a, int b, int c, int d)
{
    long m = *(long*)((char*)cb + 6);
    G_Line(a, m - b - 1, c, m - d - 1);
}