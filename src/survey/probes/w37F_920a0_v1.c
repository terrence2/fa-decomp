/* w37F v1 rva 0x920a0: G_SetColor(94), G_Box(4 shorts), set flag @+0x185, tail call */
extern void __fastcall G_SetColor(int);
extern void __stdcall G_Box(int, int, int, int);
extern void __cdecl w37f_92140(void *);

void w37f_920a0(char *s)
{
    G_SetColor(94);
    G_Box(*(short *)(s + 0x4), *(short *)(s + 0x6), *(short *)(s + 0x8),
          *(short *)(s + 0xa));
    *(s + 0x185) = 1;
    w37f_92140(s);
}