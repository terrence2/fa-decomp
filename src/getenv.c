// _getenv @ rva 0xd5de0 — lock/find/unlock around getenv lookup-table access
extern void __cdecl lockFn(int a);
extern char * __cdecl getenvLk(char *a);
extern void __cdecl unlockFn(int a);
char *getenv_q(char *name)
{
    char *s;
    lockFn(0xc);
    s = getenvLk(name);
    unlockFn(0xc);
    return s;
}
