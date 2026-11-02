// 0x8ca30 _OBJSayProc (80 B) — v1
extern void __cdecl SAYSetupFq(void);
extern void __fastcall SAYSetVarq(char **v);
extern void __fastcall SAYFinalq(char *s);
extern unsigned long __cdecl strlen(char *s);

void __cdecl OBJSayProc27(char *s)
{
    char *v[2];

    SAYSetupFq();
    if (s[0xa] == '$') {
        v[0] = (char *)s + 0xd;
        v[1] = strlen(v[0]) + (long)s + 0xe;
        SAYSetVarq(v);
    }
    SAYFinalq(s);
}