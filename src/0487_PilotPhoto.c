// ?PilotPhoto@@YIXPAUPILOT@@@Z @ rva 0x66480 (80 B) — fastcall, arg in ecx
//   (photo slot ptr): push esi / mov esi,ecx / add esi,0x95 BEFORE
//   ShellHideMouse (pointer-local form); push 0,0,0x2c0,0x8004,esi;
//   call _G_LoadBitmap@20; esi=eax; push 0x69,0x44,esi,0;
//   call _G_BlitToScreen@16 (= blit(0,h,0x44,0x69)); mov ecx,esi;
//   call @MMFreeHandle@4; ShellShowMouse; MenuCreateRemaps; pop esi.
extern void __stdcall ShellHideMouse_f(void);
extern void __stdcall ShellShowMouse_f(void);
extern void __stdcall MenuCreateRemaps_f(void);
extern unsigned short * __stdcall G_LoadBitmap_f(unsigned char *dst, int mode,
                                                 int w, int a, int b);
                                                   /* _G_LoadBitmap@20 */
extern void __stdcall G_BlitToScreen_f(int a, void *h, int c, int d);
                                                   /* _G_BlitToScreen@16 */
extern void __fastcall MMFreeHandleQ(unsigned short *h);   /* @MMFreeHandle@4 */
void __fastcall w27a_pp_q(unsigned char *dst)
{
    unsigned short *h;
    dst = dst + 0x95;
    ShellHideMouse_f();
    h = G_LoadBitmap_f(dst, 0x8004, 0x2c0, 0, 0);
    G_BlitToScreen_f(0, h, 0x44, 0x69);
    MMFreeHandleQ(h);
    ShellShowMouse_f();
    MenuCreateRemaps_f();
}