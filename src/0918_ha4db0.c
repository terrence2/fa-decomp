extern int __stdcall RMAccess(int h, int flags);
void __fastcall w32G_a4db0_v3(char *p)
{
	int h;
	char *e;
	h = *(int *)p;
	e = p;
	if (h == 0) return;
	do {
		*(int *)(e + 8) = RMAccess(*(int *)(e + 4), 0x8000);
		e += 0x1a;
	} while (*(int *)e != 0);
}
