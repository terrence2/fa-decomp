/* probe w45D_ccc0 v3 (FA 0x40ccc0, 96B): menu save brush (subMenuPos variant) */
extern unsigned short w45D_smp[2];      /* ?subMenuPos@@3UWORD_POINT@@A (VA 0x51d684) */
extern short w45D_shW;                  /* ?shadowWidth@@3FA  (FA ref 0x51d68c) */
extern short w45D_shH;                  /* ?shadowHeight@@3FA (FA ref 0x51dbcc, movsx) */
extern unsigned char *w45D_sms;         /* ?subMenuSave@@3PAUT_HANDLE@@A (0x4e81f0) */

long __stdcall G_AllocBitmap(long, long, long);
long __stdcall G_BlitToBrush(long, long, long, long);

void __fastcall w45D_ccc0(unsigned char *menu)
{
    short *wp;
    wp = (short *)(menu + 8);
    w45D_smp[0] = wp[0];
    w45D_smp[1] = wp[1];
    w45D_sms = (unsigned char *)G_AllocBitmap(wp[2] + w45D_shW,
                                              wp[3] + w45D_shH, 0x104);
    G_BlitToBrush(0, (long)w45D_sms, wp[0], wp[1]);
}