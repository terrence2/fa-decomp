/* w46A __onexit v2 = v1 with volatile beg/end to force FA's reload/mem-op forms. */
extern void          w46a_lock(void);
extern void          w46a_unlock(void);
extern unsigned long w46a_msize(unsigned long);
extern volatile unsigned long w46a_beg;           /* = __acmdln+0x8 */
extern volatile unsigned long w46a_end;           /* = __acmdln+0x4 */
extern unsigned long w46a_realloc(unsigned long, unsigned long);

void *w46a_onexit(void *arg)
{
    unsigned long x, e;

    w46a_lock();
    x = w46a_msize(w46a_beg);
    e = w46a_end - w46a_beg + 4;
    if (x < e) {
        x = w46a_msize(w46a_beg) + 0x10;
        x = w46a_realloc(w46a_beg, x);
        if (x == 0) {
            w46a_unlock();
            return 0;
        }
        e = w46a_end - w46a_beg;
        e = e & ~3UL;
        w46a_beg = x;
        w46a_end = e + x;
    }
    *(unsigned long *)w46a_end = (unsigned long)arg;
    w46a_end = w46a_end + 4;
    w46a_unlock();
    return arg;
}