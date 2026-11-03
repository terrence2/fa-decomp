/* rva 0xbba80 (768640), 48 B - vtable call (p,1,0x1000) then mirror
   results into the interior record. */
typedef int (cdecl *cbfun)(void *, int, int);

void w34g_objC(void *p)
{
    unsigned *m = *(unsigned **)((char *)p + 0x12);
    cbfun fn = *(cbfun *)((char *)p + 4);
    int r = fn(p, 1, 0x1000);
    m[6] = r;
    *m = r;
    m[1] = 0x1000;
}