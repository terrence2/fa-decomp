// 0xbe2f0 _PROJProc (64 B) — v1: switch returning handler pointers
extern void PROJMoveProcq(char t);
extern char PROJEventProcq(long l);
extern void PROJDamageProcq(void *h);
extern void PROJDispq(void);

void *PROJProc(unsigned char t)
{
    switch (t) {
    case 1:
        return (void *)PROJDispq;
    case 2:
        return (void *)PROJMoveProcq;
    case 3:
        return (void *)PROJEventProcq;
    case 4:
        return (void *)PROJDamageProcq;
    }
    return (void *)0;
}