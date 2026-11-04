/* w36D_88a20_v1: lazy-load listFont stub @ 0x88a20 (48 B).
   FA: a1 [listFont] / test jne L / push 0,0,0,0x8000,[str] /
   call _G_LoadBitmap@20 / a3 store -> [listFont] / L: ret. */
extern void *__stdcall G_LoadBitmap(void *a1, unsigned long a2, void *a3,
                                    unsigned long a4, void *a5);

extern unsigned long w36d_lf;     /* -> ?listFont@@3PAUT_HANDLE@@A */
extern unsigned char w36d_str[4]; /* -> _checkRightButton+0x220 */

void w36d_88a20(void)
{
    if (!w36d_lf)
        w36d_lf = (unsigned long)G_LoadBitmap(w36d_str, 0x8000, 0, 0, 0);
}