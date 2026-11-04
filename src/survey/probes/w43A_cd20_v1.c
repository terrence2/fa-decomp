/* rva 0xcd20 (64 B) - blit saved submenu (twin of 0xcc80)
 * FA: movsx eax,[subMenuPos+2]; movsx ecx,[subMenuPos+0]; push eax; edx=save;
 * push ecx/edx/0; call G_BlitToScreen(0,save,x,y); mov ecx,[save];
 * call MMFreeHandle(save) fastcall; c7 05 save,0; ret.
 */
extern short w43aSubPos[2];
extern char *w43aSubSave;
extern void __stdcall w43aBlit2(long, char *, long, long);
extern void __fastcall w43aMMFree2(char *);

void w43A_cd20(void)
{
    w43aBlit2(0, w43aSubSave, (long)w43aSubPos[0], (long)w43aSubPos[1]);
    w43aMMFree2(w43aSubSave);
    w43aSubSave = 0;
}