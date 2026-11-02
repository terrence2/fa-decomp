// __heap_alloc @ rva 0xd9300 — C v3 (array-deref limit compare via
// Ispunct's mem-left trick; fast path as inline if-body, fallback last —
// no goto, so FA's 39 3d / 72 jb shape and no stray ebx)
extern char heaplimitA[];                   /* __adbgmsg+0x1074 */
extern void *crtheapG;
extern void *heapAllocSubX(unsigned);
extern void __cdecl lockX(int);
extern void __cdecl unlockX(int);
__declspec(dllimport) void *__stdcall HeapAllocX(void *h, unsigned long fl, unsigned long sz);

void *__cdecl heap_allocq(unsigned long n)
{
    void *pv;
    unsigned long n2;

    n2 = (n + 0xf) & ~0xf;
    if (*(unsigned long *)heaplimitA >= n2)
    {
        lockX(9);
        pv = heapAllocSubX(n2 >> 4);
        unlockX(9);
        if (pv != 0)
            return pv;
    }
    return HeapAllocX(crtheapG, 0, n2);
}