// @SampleInit@8 @ rva 0x12270 — fastcall (ecx=obj, edx=data): if h==0
//   alloc count<<4 / 0x8000, last = count<<4+h-0x10; then do-while fill:
//   rec[0]=_currentTicks, rec[1..3]=data[0..2], p+=0x10 while p<=last.
struct w27a_sinit { long count, p1, p2, h, last; };
extern long w27a_ticks;                                   /* _currentTicks */
extern long __fastcall MMAllocPtr_f(long n, long flags);  /* @MMAllocPtr@8 */
void __fastcall w27a_sam_q(struct w27a_sinit *obj, long *data)
{
    long *p, *last;
    if (obj->h == 0)
    {
        obj->h = MMAllocPtr_f(obj->count << 4, 0x8000);
        obj->last = (obj->count << 4) + obj->h - 0x10;
    }
    p = (long *)obj->h;
    last = (long *)obj->last;
    if (p <= last)
    {
        do {
            p[0] = w27a_ticks;
            p[1] = data[0];
            p[2] = data[1];
            p[3] = data[2];
            p += 4;
        } while (p <= last);
    }
}
