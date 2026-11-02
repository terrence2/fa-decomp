// n1 get_osfhandle v9: idx ops first (FA order), grp = (fd & ~0x18) >> 3
// on the signed fd (sar), scale-1 __pioinfo row load, byte FOPEN mem test.
extern unsigned long nhandleX;
extern char pioinfoX;
extern long *errnoX(void);
extern long *setDosErrnoX(void);

long get_osfhandle_r(int fd)
{
    unsigned long o2, blk, p;
    if ((unsigned long)fd >= nhandleX)
        goto fail;
    o2 = (unsigned long)(fd & 0x1f);
    o2 <<= 2;
    blk = (fd & ~0x18) >> 3;
    o2 = o2 + o2 * 8;
    p = *(unsigned long *)((char *)&pioinfoX + blk);
    p += o2;
    if (*(unsigned char *)(p + 4) & 1)
        return *(long *)p;
fail:
    *(long *)errnoX() = 9;
    *(long *)setDosErrnoX() = 0;
    return -1;
}
