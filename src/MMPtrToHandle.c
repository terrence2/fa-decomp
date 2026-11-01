// MMPtrToHandle @ rva 0x35c70 — decompiled from FA.EXE (probe d218_mpth2.c, byte-exact)
extern void *mmUsedList;
void * __fastcall MMPtrToHandle_q(int p1)
{
    void *l;
    if (p1 == 0)
        return 0;
    l = mmUsedList;
    if (l == 0)
        return 0;
    do
    {
        if (*(long *)((char *)l + 8) == p1)
            return l;
        l = *(void **)l;
    } while (l != 0);
    return 0;
}
