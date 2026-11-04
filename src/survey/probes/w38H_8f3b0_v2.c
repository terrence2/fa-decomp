/* probe 38H: OBJInit @ rva 0x8f3b0 - reset object globals: alloc 0x8000 pool, init counters */
typedef void *OBJP;
extern OBJP __fastcall MMAllocPtr(OBJP a1, int a2);
extern char thisComputerX;
extern unsigned short nextObjIdW;
extern OBJP objInitCur;
extern OBJP wingSayXe64;
extern OBJP comTypX858;
extern unsigned long comTypX860;
extern unsigned long comTypX85c;
extern unsigned long nextIdP4;

unsigned char __stdcall OBJInit(void *o)
{
	OBJP v;
	int n;
	unsigned t;
	unsigned t2;
	objInitCur = o;
	v = MMAllocPtr(o, 0x8000);
	n = -20 - (int)thisComputerX;
	wingSayXe64 = v;
	comTypX858 = v;
	nextObjIdW = 1;
	t = 5 * n;
	t = 5 * t;
	t = 5 * t;
	t = 8 * t;
	comTypX860 = t;
	t2 = t - 0x3e7;
	comTypX85c = t2;
	nextIdP4 = t2;
	return 1;
}
