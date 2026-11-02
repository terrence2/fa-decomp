// ?CN_GetString@@YAJPADPAE@Z @ rva 0x7e490 (32 B) — network get-string thunk.
// FA: eax=[esp+8](arg2); push 0x14; ecx=[esp+8](arg1); push 0x19; push 0x28;
// push &_fmtReduceButtonH+0x19c; push eax; push ecx; call ?_GetString@@YAJPAD00JJJ@Z;
// add esp,0x18; ret (6 cdecl args: (a, b, str, 0x28, 0x19, 0x14)).
extern char cnStr[];   /* _fmtReduceButtonH+0x19c */
extern int __cdecl GetStringQ(char *a, char *b, char *str,
                              unsigned long j4, unsigned long j5,
                              unsigned long j6);

long __cdecl CN_GetString(char *a, unsigned char *b)
{
    return GetStringQ(a, (char *)b, cnStr, 0x28, 0x19, 0x14);
}
