/* probe w45D_adf20 (FA 0x4adf20, 96B): ring-window 4-byte fetch with wrap stitch */
void *memcpy(void *, const void *, unsigned long);

void w45D_adf20(unsigned char *rb, unsigned long off, unsigned char *dst)
{
    long n;
    n = *(long *)(rb + 8) - off;
    if ((unsigned long)n < 4) {
        memcpy(dst, rb + 0x11 + off, n);
        memcpy(dst + n, rb + 0x11, 4 - n);
    } else {
        *(unsigned long *)dst = *(unsigned long *)(rb + 0x11 + off);
    }
}