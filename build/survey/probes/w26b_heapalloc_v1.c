// __heap_alloc @ rva 0xd9300 — C v1
extern void *heapAllocSubX(unsigned);
extern void __cdecl lockX(int);
extern void __cdecl unlockX(int);
extern void *crtheapG;
extern unsigned long heaplimitG[];
__declspec(dllimport) void *__stdcall HeapAllocX(void *h, unsigned long fl, unsigned long sz);

void *__cdecl heap_allocq(unsigned long n)
{
    void *pv;
    n = (n + 15) & 0xfffffff0;
    if (*(unsigned long *)heaplimitG >= n)
    {
        lockX(9);
        pv = heapAllocSubX(n >> 4);
        unlockX(9);
        if (pv != 0)
            return pv;
    }
    return HeapAllocX(crtheapG, 0, n);
}
