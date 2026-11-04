/* rva 0xbba80 (768640), 48 B - v4: callee kept inline in the call expr. */
typedef int (cdecl *cbfun)(void *, int, int);

void w34g_objC4(void *p)
{
    unsigned *m = *(unsigned **)((char *)p + 0x12);
    int r = (*(cbfun *)*(void **)((char *)p + 4))(p, 1, 0x1000);
    m[6] = r;
    *m = r;
    m[1] = 0x1000;
}