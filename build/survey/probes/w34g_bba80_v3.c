/* rva 0xbba80 (768640), 48 B - callee in ebx (first decl), record load in
   esi (second decl), call fn(p,1,0x1000). */
typedef int (cdecl *cbfun)(void *, int, int);

void w34g_objC3(void *p)
{
    cbfun fn = *(cbfun *)*(void **)((char *)p + 4);
    unsigned *m = *(unsigned **)((char *)p + 0x12);
    int r = fn(p, 1, 0x1000);
    m[6] = r;
    *m = r;
    m[1] = 0x1000;
}