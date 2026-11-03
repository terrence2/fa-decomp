typedef unsigned char uchar;
extern uchar cColor;
extern uchar cFillType;
extern char *cRemapTable;
extern char spxFh8[];
extern uchar tempYLR[];
extern uchar temp2YLR[];
void __fastcall w33D_GSet(int c)
{
	uchar f;
	if ((f = *(uchar *)spxFh8) == 0)
		return;
	if (c >= 0x100)
	{
		cColor = tempYLR[c * 2 + 0x4c78];
		cFillType = temp2YLR[c + 0x4d28];
		cRemapTable = (char *)(*(unsigned long *)&tempYLR[c * 4 + 0x4cc0]);
	}
	else
	{
		cFillType = 0;
		cColor = (uchar)c;
	}
}