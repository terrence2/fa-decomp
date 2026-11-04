/* probe 38H: SEQpalette @ rva 0x46200 - load palette file -> memmove into curPalette */
extern int __stdcall LoadFile(int a1, unsigned *a2, int a3, int a4);
extern void * __fastcall MMAccessR(int a1);
extern void __fastcall MMFreeHandle(int a1);
extern void *memmove(void *dst, const void *src, unsigned n);
extern char curPaletteX;

void SEQpalette(int a1, int a2, int a3)
{
	unsigned h;
	short n;
	int q;
	int hh;
	void *src;
	hh = LoadFile(a1, &h, 0, 0x8104);
	src = MMAccessR(hh);
	if (a3 == 0)
		q = a2 + h / 3 - 1;
	else
		q = a3;
	n = (short)(q - a2);
	++n;
	memmove((char *)&curPaletteX + 3 * a2, src, 3 * (int)n);
	MMFreeHandle(hh);
}
