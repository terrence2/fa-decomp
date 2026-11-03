/* rva 0xb3c30 (736304), 48 B - vtable method: loop-call once, then
   word field sets 200/100 by cmp,1/sbb mask chain. */
typedef void (cdecl *cbfun)(void *, int);

void w34g_objA(void *wp)
{
    int n = 1;
    do
    {
        (*(cbfun)(*(char **)((char *)wp + 4) + 0x24))(wp, n);
    } while (--n);
    *(int *)((char *)wp + 0xe) =
        *(unsigned char *)((char *)wp + 0xc) ? 200 : 100;
}