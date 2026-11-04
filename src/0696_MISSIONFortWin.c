/* probe 38H: MISSIONFortWin @ rva 0x84430 - win if no living fort passes flags */
extern unsigned short nextObjIdG;
extern unsigned *_objPtrsG;
extern char __fastcall Alive(const void *o);

char __stdcall MISSIONFortWin(long wp)
{
	int r;
	unsigned short i;
	unsigned e;
	unsigned w;
	char alive;
	r = 1;
	i = 1;
	while ((unsigned short)i < (unsigned short)nextObjIdG) {
		e = (unsigned)i & 0xffff;
		w = (unsigned)_objPtrsG[e];
		w = *(unsigned *)((char *)w + 1);
		if (w & 1)
			alive = (char)(Alive(w) != 0);
		else
			alive = 0;
		if ((w & (unsigned)wp) != 0)
			if (alive != 0)
				if (r > 0)
					r = 0;
		i++;
	}
	return (char)r;
}
