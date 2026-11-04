extern unsigned char tdic[];
extern long tdicSize;
char __stdcall T_NamedTmaps(void)
{
    char r;
    unsigned long n;
    r = 0;
    if ((char *)tdic + tdicSize * 53 > (char *)tdic) {
        n = ((unsigned long)tdicSize * 53 + 0x34) / 53;
        do {
            if (tdic[0]) r = 1;
        } while (--n);
    }
    return r;
}