/* rva 0x1d390 (119696), 48 B - stricmp two _items records (stride 48,+17). */
extern char w33g_items[];                          /* -> _items */
extern int __cdecl w33g_sicmp(char *, char *);     /* -> _stricmp */

void __fastcall w33g_icmp(int a, int b)
{
    w33g_sicmp(w33g_items + a * 48 + 17, w33g_items + b * 48 + 17);
}
