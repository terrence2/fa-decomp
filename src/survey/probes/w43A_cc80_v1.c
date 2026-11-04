/* rva 0xcc80 (64 B) - blit saved menu screen
 * FA: movsx eax,[menuSavePos+2]; movsx ecx,[menuSavePos+0]; push eax; edx=brush;
 * push ecx/edx/0; call G_BlitToScreen(0,brush,x,y); mov ecx,[brush];
 * call MMFreeHandle(brush) fastcall; c7 05 brush,0; ret.
 * RIGHT-TO-LEFT: arg4=+2 first, arg3=+0.
 */
extern short w43aSavePos[2];
extern char *w43aSaveBrush;
extern void __stdcall w43aBlit(long, char *, long, long);
extern void __fastcall w43aMMFree(char *);

void w43A_cc80(void)
{
    w43aBlit(0, w43aSaveBrush, (long)w43aSavePos[0], (long)w43aSavePos[1]);
    w43aMMFree(w43aSaveBrush);
    w43aSaveBrush = 0;
}