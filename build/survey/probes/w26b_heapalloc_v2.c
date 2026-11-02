// __heap_alloc @ rva 0xd9300 — C v2 (n2 first, limit value-extern, goto fallback)
extern void *heapAllocSubX(unsigned);
extern void __cdecl lockX(int);
extern void __cdecl unlockX(int);
extern void *crtheapG;
extern unsigned long heaplimitG;
__declspec(dllimport) void *__stdcall HeapAllocX(void *h, unsigned long fl, unsigned long sz);

void *__cdecl heap_allocq(unsigned long n)
{
    void *pv;
    unsigned long n2;

    n2 = (n + 0xf) & ~0xf;
    if (heaplimitG < n2)
        goto fallback;
    lockX(9);
    pv = heapAllocSubX(n2 >> 4);
    unlockX(9);
    if (pv == 0)
fallback:
        return HeapAllocX(crtheapG, 0, n2);
    return pv;
}
