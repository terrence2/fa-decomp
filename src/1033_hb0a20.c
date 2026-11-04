/* rva 723488 (0xb0a20) v2 — decl order c1-first to steer CL colors
 * toward FA (c1 in esi, x in edi); v1 had x=esi/c1=edi. */
extern char *w40E_strchr(const char *, int);
extern long __stdcall w40E_Rand(void);
extern long __cdecl w40E_Sprintf(char *, const char *, ...);
extern char w40E_pcr[];

void __cdecl w40E_ColStr(char *p)
{
    long c1;
    char *x;

    x = w40E_strchr(p, 0x2a);
    if (x == 0) return;
    c1 = x[1] - 0x30;
    w40E_Sprintf(x, &w40E_pcr[0x1f],
                 (short)w40E_Rand() + (c1 & 0xffff));
}