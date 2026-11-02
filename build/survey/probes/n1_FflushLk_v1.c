// n1 FflushLk: flush-then-commit; the <1 ? 0 : -1 borrow tail is FA's own
// adc form; the _IOCOMMIT byte test is the mem test family.
extern int __cdecl _flush_lk(void *f);
extern int __cdecl _commit(int fd);

int __cdecl _fflush_lk_q(void *f)
{
    int c;
    if (_flush_lk(f))
        return -1;
    if (*(unsigned char *)((char *)f + 0xd) & 0x40) {
        c = _commit(*(int *)((char *)f + 0x10));
        return (unsigned long)c < 1 ? 0 : -1;
    }
    return 0;
}
