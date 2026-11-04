// __isindst @ rva 0xe4040 — lock/find/unlock around the DBCS lead-byte table
extern void __cdecl lockFn(int a);
extern char * __cdecl isdLk(char *a);
extern void __cdecl unlockFn(int a);
char *isindst_q(char *name)
{
    char *s;
    lockFn(0xb);
    s = isdLk(name);
    unlockFn(0xb);
    return s;
}
