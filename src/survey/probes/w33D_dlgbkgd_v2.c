extern int __stdcall RMChangeType(int, char *, void *);
extern int __stdcall SetupBitmapAccess(int, int, int);
extern int __stdcall RMAccessHandle(int, void *);
extern int __stdcall G_BlitToScreen(int, int, int, int);
extern int __stdcall RMFree(void *);
extern char remapDarkenTbl[];
void __fastcall w33D_DlgBkgd(int p)
{
	unsigned char buf[0x10];
	int h;
	RMChangeType(p, remapDarkenTbl + 0x18, buf);
	SetupBitmapAccess(0x100, 0, 0);
	h = RMAccessHandle(0x8104, buf);
	G_BlitToScreen(0, h, 0, 0);
	RMFree(buf);
}