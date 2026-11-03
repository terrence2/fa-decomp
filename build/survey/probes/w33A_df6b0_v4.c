extern char *g54(void);
extern int setdp(void);

char *w33A_df6b0_v4(void)
{
    long v;
    int e;
    char *r;
    v = *(long *)g54();
    __asm fninit
    e = setdp();
    if (v) {
        r = *(char **)(v + 4);
        if (*(long *)r & 0x10008) {
            *(long *)(r + 0x20) = 0;
            *(long *)(r + 0x24) = 0xffff;
            r += 0x1c;
        }
        return r;
    }
    return (char *)e;
}
