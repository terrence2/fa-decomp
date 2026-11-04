/* w36C 0x1d440 (unnamed, 48 B) v2: signed n (FA latch is jg = signed,
 * CL emitted ja for the unsigned-long decl).  Rest of v1 was byte-exact. */
extern unsigned long numItems;   /* identity _numItems */
extern void *items;              /* identity _items */

void *__fastcall MMReallocPtr(void *a, unsigned long n);

void f_1d440(void)
{
    long n = (long)numItems;
    void *p;

    if (n <= 1)
        n = 1;
    p = MMReallocPtr(items, n * 48);
    if (p != (void *)0)
        items = p;
}