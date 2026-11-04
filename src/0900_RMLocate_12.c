/* probe 38H: RMLocate @ rva 0xa3790 - scan resList table for free slot, copy name, upper it */
extern void *resListX;
extern int resEndX;
extern unsigned char mmAllocIdX;
char *strcpy();

void __stdcall RMLocate(char *name, unsigned char flag, int data)
{
	char *cur;
	char *q;
	char c;
	cur = (char *)&resListX;
	while (*cur != 0) {
		cur += 0x13;
		if ((unsigned)cur >= (unsigned)&resEndX)
			return;
	}
	strcpy(cur, name);
	for (q = cur; *q != 0; q++) {
		c = *q;
		if (c >= 'a' && c <= 'z')
			*q = c - 0x20;
	}
	((unsigned char *)cur)[0xd] = mmAllocIdX;
	((unsigned char *)cur)[0xe] = flag;
	*(int *)(cur + 0xf) = data;
}
