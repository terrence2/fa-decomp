/* ?HUDDrawStability@@YIXXZ (96 B) - fastcall void(void): gated on hud+0x2b1
   byte; G_SetFont(hud+0x5e); ch = HUDSetStability()+0x40 stored a2-style to
   hudslewLimitHdg+0x10c; G_Print(x=unitRight+0x14, y=unitRight+0x16 -
   hud+0x4d*3 + hud+0x26f, 5, &that string) with x/y fastcall in ecx/edx and
   the two stack pushes (string first, 5 second); G_SetFont(hud+0x45). */
extern unsigned char w43c_hb1;    /* _hud+0x2b1 */
extern unsigned long w43c_f5e;    /* _hud+0x5e */
extern unsigned long w43c_f4d;    /* _hud+0x4d */
extern unsigned long w43c_f45;    /* _hud+0x45 */
extern short w43c_ur14;           /* _unitRight+0x14 */
extern short w43c_ur16;           /* _unitRight+0x16 */
extern short w43c_h26f;           /* _hud+0x26f */
extern char w43c_hdgch;           /* ?hudslewLimitHdg@@3UWORD_POINT@@A+0x10c */
extern long __fastcall w43c_gfont(unsigned long f);    /* @G_SetFont@4 */
extern long __fastcall w43c_gprintq(int x, int y, int n, char *s);
                                                  /* @G_Print@16 */
extern long __fastcall w43c_hstabq(void);         /* ?HUDSetStability@@YIJXZ */
void __fastcall w43C_hudsq(void)
{
    if (w43c_hb1) {
        w43c_gfont(w43c_f5e);
        w43c_hdgch = w43c_hstabq() + 0x40;
        w43c_gprintq(w43c_ur14, w43c_ur16 - w43c_f4d * 3 + w43c_h26f, 5,
                     &w43c_hdgch);
        w43c_gfont(w43c_f45);
    }
}
