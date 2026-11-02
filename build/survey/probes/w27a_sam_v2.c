// @SampleInit@8 v2 — locals declared after the branch so CL does not spill
// them to the stack (FA keeps h/last/p/q/ticks all enregistered); alloc
// add/sub split into two statements to block the dec<<4 fold.
struct w27a_sinit { long count, p1, p2, h, last; };
extern long w27a_ticks;                                   /* _currentTicks */
extern long __fastcall MMAllocPtr_f(long n, long flags);  /* @MMAllocPtr@8 */
void __fastcall w27a_sam_q(struct w27a_sinit *obj, long *data)
{
    long *p, *last, *q, t;
    if (obj->h == 0)
    {
        obj->h = MMAllocPtr_f(obj->count << 4, 0x8000);
        t = (obj->count << 4) + obj->h;
        obj->last = t - 0x10;
    }
    p = (long *)obj->h;
    last = (long *)obj->last;
    if (p <= last)
    {
        do {
            q = p + 1;
            p[0] = w27a_ticks;
            q[0] = data[0];
            q[1] = data[1];
            q[2] = data[2];
            p += 4;
        } while (p <= last);
    }
}
