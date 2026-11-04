/* w45H 0x91f10: print centered curDialog text (mixed-reg G_* callees) */
typedef unsigned long ulong;

extern ulong __stdcall RMAccessHandle(ulong, void *);       /* _RMAccessHandle@8 */
extern ulong __stdcall ColorStringWidth(int, int);          /* -> @G_ColorStringWidth@8 */
extern void __stdcall ColorPrint(int, int, int, int, int);  /* -> @G_ColorPrint@20 */
extern void *curDialog;                                     /* _curDialog = ?curDialog@@3PAUDIALOG@@A */
extern char panelFont;                                      /* _panelFont = ?videoInitialized@@3DA (+0x3fc) */

void w45H_91f10(ulong a0)
{
    ulong esih = RMAccessHandle(0x8000, (void *)((char *)&panelFont + 0x3fc));
    int x;
    x = (int)ColorStringWidth(
        (int)*(short *)((char *)curDialog + 0xa) + 7, 0);
    x = (int)*(short *)((char *)curDialog + 0xc) - x;
    ColorPrint(0, 0, 0, 0,
        (int)*(short *)((char *)curDialog + 8) + (x >> 1));
}