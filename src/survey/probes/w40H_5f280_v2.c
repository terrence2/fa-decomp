/* w40H @GRPAttackingObj@4 @ 0x5f280 v2 — short param used directly as
 * 16-bit (FA mov si,cx), bit=1 kept as a variable (FA keeps it in ebp,
 * SIB [ebp*4 + _groupIds], and masks with test [eax+1],ebp — the word
 * index is bit*2 of the ushort view of _groupIds). */
extern unsigned short curIdW;         /* -> _curId */
extern unsigned short groupIdsW[];    /* -> _groupIds */
extern unsigned char groupSizesB[];   /* -> _groupSizes */
extern unsigned char __stdcall GRPPartW(unsigned short id, long *out, long z);
extern long __fastcall OBJGetW(unsigned short w);

long __fastcall w40h5f280(short id)
{
	long grp, i, n, bit;
	char *o;

	if (!GRPPartW(curIdW, &grp, 0))
		return 0;
	n = 0;
	bit = 1;
	for (i = 0; (long)groupSizesB[grp] > i; i++) {
		o = (char *)OBJGetW(((unsigned short *)groupIdsW)[2 * bit]);
		if (*(long *)(o + 1) & bit)
			if (*(unsigned char *)(o + 0xe3) == 0x20 &&
			    *(unsigned short *)(o + 0xee) == (unsigned short)id)
				n++;
	}
	return n;
}
