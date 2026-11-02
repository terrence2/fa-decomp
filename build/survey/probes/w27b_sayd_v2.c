// 0x8b520 _SAYDefaultSayProc (80 B) — v2 (#pragma function(strlen): CL 4.2
// otherwise expands strlen to the repz-scasb intrinsic)
#pragma function(strlen)
extern void __cdecl SAYSetupFq(void);
extern void __fastcall SAYSetVarq(char **v);
extern void __fastcall SAYFinalq(char *s);
extern unsigned long __cdecl strlen(char *s);

void __cdecl SAYDefaultSayProc27(char *s)
{
    char *v[2];

    SAYSetupFq();
    if (s[0xa] == '$') {
        v[0] = (char *)s + 0xd;
        v[1] = (char *)strlen(v[0]) + (long)s + 0xe;
        SAYSetVarq(v);
    }
    SAYFinalq(s);
}
