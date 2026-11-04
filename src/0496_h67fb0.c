/* probe 38H: unnamed fastcall @ rva 0x467fb0 - strcpy(dst,src); truncate dst at delimiter; cap 0x17 */
extern char *strstr(char *s, const char *f);
extern int pilotsX204;

void __fastcall w38hStrtDel(char *src, char *dst)
{
	char *q;
	strcpy(dst, src);
	q = strstr(dst, (char *)&pilotsX204);
	if (q != 0)
		*q = 0;
	*(char *)(dst + 0x17) = 0;
}
