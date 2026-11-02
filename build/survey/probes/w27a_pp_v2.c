// PilotPhoto — int intermediate defeats lea fold -> mov esi,ecx; add esi,0x95.
extern void __stdcall ShellHideMouse_f(void);
extern void __stdcall ShellShowMouse_f(void);
extern void __stdcall MenuCreateRemaps_f(void);
extern unsigned short * __stdcall G_LoadBitmap_f(unsigned char *dst, int mode,
                                                 int w, int a, int b);
extern void __stdcall G_BlitToScreen_f(int a, void *h, int c, int d);
extern void __fastcall MMFreeHandleQ(unsigned short *h);   /* @MMFreeHandle@4 */
void __fastcall w27a_pp_q(unsigned char *dst)
{
    int d;
    unsigned short *h;
    d = (int)dst;
    d = d + 0x95;
    dst = (unsigned char *)d;
    ShellHideMouse_f();
    h = G_LoadBitmap_f(dst, 0x8004, 0x2c0, 0, 0);
    G_BlitToScreen_f(0, h, 0x44, 0x69);
    MMFreeHandleQ(h);
    ShellShowMouse_f();
    MenuCreateRemaps_f();
}
