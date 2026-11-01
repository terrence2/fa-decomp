// MMFreeAllId @ rva 0x35cf0 — decompiled from FA.EXE (probe d203_mfdi.c, byte-exact)
extern void *mmUsedList;
extern void __fastcall MMFreeHandle(int a);
void __fastcall MMFreeAllId_q(int p1)
{
    void *n;
    void *nxt;
    char id;
    id = (char)p1;
    n = mmUsedList;
    while (n != 0)
    {
        nxt = *(void **)n;
        if (*(unsigned char *)((char *)n + 0x12) == (unsigned char)id)
            MMFreeHandle((int)n);
        n = nxt;
    }
}
