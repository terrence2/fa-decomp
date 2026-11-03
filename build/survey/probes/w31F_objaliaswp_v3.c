/* w31F / _OBJAliasWaypoint@16 v3: volatile re-read of p->f4 after the store
 * so CL cannot store-forward r into the compare (FA re-reads the memory). */
extern long __fastcall OBJAlias(short id, char flag);
extern long __stdcall OBJAliasPreferred(unsigned long a, char b,
                                        unsigned short c, unsigned short d);

void __stdcall OBJAliasWaypoint(char *p, char c1, unsigned short w1,
                                unsigned short w2)
{
    unsigned short w1t, w2t, r;
    char c1v;
    if (*(unsigned char *)(p + 3) == 2) {
        c1v = c1;
        r = (unsigned short)OBJAlias(*(unsigned short *)(p + 4), c1v);
        w2t = w2;
        *(unsigned short *)(p + 4) = r;
        w1t = w1;
        if (*(volatile unsigned short *)(p + 4) == w1t)
            *(unsigned short *)(p + 4) = w2t;
    } else {
        w1t = w1;
        c1v = c1;
        w2t = w2;
    }
    if (*(unsigned long *)(((char *)p) + 0x21))
        *(unsigned long *)(((char *)p) + 0x21) = OBJAliasPreferred(
            *(unsigned long *)(((char *)p) + 0x21), c1v, w1t, w2t);
}