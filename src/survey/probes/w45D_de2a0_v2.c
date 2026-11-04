/* probe w45D_de2a0 (FA 0x4de2a0, 81B): debug-heap region search */
extern unsigned char _adbgmsg[];        /* FA global __adbgmsg (VA 0x51b500) */

long w45D_de2a0(unsigned long addr, unsigned long *o1, unsigned long *o2)
{
    unsigned long n, st, page;
    long diff;

    n = (unsigned long)_adbgmsg;
    while (1) {
        st = *(unsigned long *)(n + 0x810);
        if (st != 0 && addr > st) {
            if (addr < st + 0x400000)
                break;
        }
        n = *(unsigned long *)n;
        if (n == (unsigned long)_adbgmsg)
            return 0;
    }
    *o1 = n;
    page = addr & 0xfffff000;
    diff = addr - page;
    *o2 = page;
    return page + 8 + ((diff - 0x100) >> 4);
}