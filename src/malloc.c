// _malloc @ rva 0xd9290 — forwarder to __nh_malloc with FA's __newmode
//   allocation mode (probe d87 exact; double-underscore names decorate to
//   ___newmode/___nh_malloc -> identity maps in swap.json).
extern unsigned long __newmode;
extern void *__nh_malloc(unsigned long n, unsigned long mode);

void *_malloc_q(unsigned long n)
{
    return __nh_malloc(n, __newmode);
}
