extern char *g54(void);
extern void setdp(void);
extern unsigned long gflag;

char *w33A_df6b0_v1(void)
{
    long v;
    char *r;
    v = *(long *)g54();
    __asm fninit
    setdp();
    if (v) {
        r = *(char **)(v + 4);
        if (*(long *)r & 0x10008)
            r += 0x1c;
    }
    return r;
}