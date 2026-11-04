extern void __fastcall MMFreeHandle(int);
extern void __cdecl w34f_dfree(void *);
extern void __cdecl w34f_fnode(void *);
void __cdecl w34f_dealloc(void *vdo, void *list);
void __cdecl w34f_dealloc(void *vdo, void *list)
{
    void *n;
    void *p;
    if (*(int *)((char *)vdo + 0xe) != 0)
        MMFreeHandle(*(int *)((char *)vdo + 0xe));
    if (*(void **)((char *)vdo + 0x20) != 0)
        w34f_dfree(*(void **)((char *)vdo + 0x20));
    if (*(void **)((char *)vdo + 0x1c) != 0)
        w34f_dfree(*(void **)((char *)vdo + 0x1c));
    if (*(int *)((char *)vdo + 0x24) != 0)
        MMFreeHandle(*(int *)((char *)vdo + 0x24));
    for (p = list; p != 0; p = n) {
        n = *(void **)((char *)p + 8);
        w34f_fnode(p);
    }
}