/* rva 0xb3c30 (736304), 48 B - vtable slot call through [vt+0x24] */
typedef void (cdecl *cbfun)(void *, int);

void w34g_objA2(void *wp)
{
    int n = 1;
    do
    {
        (*(cbfun *)((char *)*(char **)((char *)wp + 4) + 0x24))(wp, n);
    } while (--n);
    *(int *)((char *)wp + 0xe) =
        *(unsigned char *)((char *)wp + 0xc) ? 200 : 100;
}