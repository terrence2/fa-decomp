/* rva 0x1d390 (119696), 48 B - stricmp two _items records (stride 48,+17):
   FA loads the _items pointer variable once into eax (a1 moffs). */
extern char *w33g_itp;                         /* -> _items (pointer var) */
extern int __cdecl w33g_sicmp(char *, char *); /* -> _stricmp */

void __fastcall w33g_icmp(int a, int b)
{
    char *it;
    it = w33g_itp;
    w33g_sicmp(it + a * 48 + 17, it + b * 48 + 17);
}
