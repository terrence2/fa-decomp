// 0x8ca30 _OBJSayProc (80 B) — b1: single-case switch on the char field
#pragma function(strlen)
extern void __cdecl SAYSetupFq(void);
extern void __fastcall SAYSetVarq(char **v);
extern void __fastcall SAYFinalq(char *s);
extern unsigned long __cdecl strlen(char *s);

void __cdecl OBJSayProcB1(char *s)
{
    char *v[2];

    SAYSetupFq();
    switch (s[0xa]) {
    case '$':
        v[0] = (char *)s + 0xd;
        v[1] = (char *)strlen(v[0]) + (long)s + 0xe;
        SAYSetVarq(v);
        break;
    }
    SAYFinalq(s);
}