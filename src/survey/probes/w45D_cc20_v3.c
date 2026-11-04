/* probe w45D_cc20 v3 (FA 0x40cc20, 96B): menu save brush (menuSavePos variant) */
extern unsigned short w45D_msp[2];      /* ?menuSavePos@@3UWORD_POINT@@A (VA 0x51dbac) */
extern short w45D_shW;                  /* ?shadowWidth@@3FA  (FA ref 0x51d68c, movsx) */
extern short w45D_shH;                  /* ?shadowHeight@@3FA (FA ref 0x51dbcc, movsx) */
extern unsigned char *w45D_msb;         /* ?menuSaveBrush@@3PAUT_HANDLE@@A (0x4e81ec) */

long __stdcall G_AllocBitmap(long, long, long);
long __stdcall G_BlitToBrush(long, long, long, long);

void __fastcall w45D_cc20(unsigned char *menu)
{
    short *wp;
    wp = (short *)(menu + 8);
    w45D_msp[0] = wp[0];
    w45D_msp[1] = wp[1];
    w45D_msb = (unsigned char *)G_AllocBitmap(wp[2] + w45D_shW,
                                              wp[3] + w45D_shH, 0x104);
    G_BlitToBrush(0, (long)w45D_msb, wp[0], wp[1]);
}