/* rva 0xb3c60 (736352), 48 B - optional vtable slot call, then null the
   slot and the word field. */
typedef void (cdecl *cbfun)(void *);

void w34g_objB2(void *sp)
{
    void *fn = *(void **)((char *)sp + 4);
    if (fn != 0)
    {
        (*(cbfun *)((char *)fn + 0x28))(sp);
    }
    *(int *)((char *)sp + 4) = 0;
    *(int *)((char *)sp + 0xe) = 0;
}