extern int RMChangeType(int, char *, void *);
extern int SetupBitmapAccess(int, int, int);
extern int RMAccessHandle(int, void *);
extern int G_BlitToScreen(int, int, int, int);
extern int RMFree(void *);
extern char remapDarkenTbl[];
void __fastcall w33D_DlgBkgd(int p)
{
	unsigned char buf[0x10];
	RMChangeType(p, remapDarkenTbl + 0x18, buf);
	SetupBitmapAccess(0x100, 0, 0);
	G_BlitToScreen(0, RMAccessHandle(0x8104, buf), 0, 0);
	RMFree(buf);
}