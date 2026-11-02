/* probe v2: dcs assigned first; zero as register local; plain ptr cmp */
typedef void (__stdcall *PCSFN)(void *);
extern PCSFN _dcsIAT;        /* __imp__DeleteCriticalSection slot content */
extern void _frea(void *q);  /* chunk 0xd8130 */
extern char _qStart;         /* __crtheap+4  (imm32 in code) */
extern char _qEnd;           /* __nhandle    (imm32 in code) */

void __cdecl __ioterm_q(void)
{
    PCSFN dcs;
    unsigned char *c;
    void **q;
    void *t;
    unsigned long z;

    dcs = _dcsIAT;
    q = (void **)&_qStart;
    do {
        t = *q;
        if (t != 0) {
            unsigned long b0;
            c = (unsigned char *)t;
            z = 0;
            if ((unsigned char *)((unsigned long)c + 0x480) > (unsigned char *)t) {
                do {
                    if (((unsigned long *)c)[2] != z)
                        dcs((void *)(c + 0xc));
                    c += 0x24;
                } while ((unsigned long)*(unsigned long **)q + 0x480 > (unsigned long)c);
            }
            _frea((void *)*(void **)q);
        }
        q += 1;
    } while (q < (void **)&_qEnd);
}
