/* v4: the three -1 stores use the COMMON old-ofs base with element
 * indices [0],[1],[2] (FA's disps -0x30/-0x2c/-0x28 relative to f14 + the
 * advanced esi), and ofs += 48 moved after the stores (FA schedules the
 * esi advance early with compensating negative disps). */
extern void *memset(void *, int, unsigned);

struct W36G_WRAP { long d[12]; };
struct W36G_SQ { unsigned long f0, f4, f8, fc, f10; struct W36G_WRAP *f14; };

void InitializeQueue(struct W36G_SQ *q, struct W36G_WRAP *w, long n)
{
    long ofs;
    q->f14 = w;
    q->f0 = 0;
    q->f4 = 0;
    q->fc = 0;
    q->f10 = 0;
    q->f8 = n;
    if (n > 0) {
        ofs = 0;
        do {
            memset((char *)q->f14 + ofs, 0, 48);
            ((long *)((char *)q->f14 + ofs))[0] = -1;
            ((long *)((char *)q->f14 + ofs))[1] = -1;
            ((long *)((char *)q->f14 + ofs))[2] = -1;
            ofs += 48;
            n--;
        } while (n != 0);
    }
}