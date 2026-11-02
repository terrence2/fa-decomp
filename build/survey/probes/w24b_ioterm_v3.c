/* probe v3: q declared/assigned first */
typedef void (__stdcall *PCSFN)(void *);
extern PCSFN _dcsIAT;        /* __imp__DeleteCriticalSection slot content */
extern void _frea(void *q);  /* chunk 0xd8130 */
extern char _qStart;         /* __crtheap+4  (imm32 in code) */
extern char _qEnd;           /* __nhandle    (imm32 in code) */

void __cdecl __ioterm_q(void)
{
    void **q;
    PCSFN dcs;
    unsigned char *c;
    void *t;
    unsigned long z;

    q = (void **)&_qStart;
    dcs = _dcsIAT;
    do {
        t = *q;
        if (t != 0) {
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
