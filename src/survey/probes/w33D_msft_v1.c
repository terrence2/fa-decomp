extern int missionSucceeded;
extern int thisComputer;
extern short objControlledBy[];
extern char *objPtrs[];
int w33D_msft(void)
{
	int r = missionSucceeded;
	char x1, x2;
	char *a, *b;
	unsigned short m0, m;
	if (!thisComputer)
		return r;
	m0 = *(unsigned short *)objControlledBy;
	if (!m0)
		return r;
	m = objControlledBy[thisComputer];
	if (!m)
		return r;
	a = objPtrs[m0];
	b = objPtrs[m];
	x1 = a[9];
	x2 = b[9];
	if ((x1 ^ x2) & 0x80)
		return -r;
	return r;
}