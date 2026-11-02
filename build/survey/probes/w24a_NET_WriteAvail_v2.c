extern unsigned long __cdecl validate_player(long h);
extern unsigned char ws_x[];

long __cdecl NET_WriteAvail(long h)
{
    unsigned long p;
    long r = 0;
    if (*(unsigned char *)ws_x) {
        p = (unsigned long)validate_player(h);
        if (p) {
            long a = *(long *)((char *)p + 0x2c8e);
            long b = *(long *)((char *)p + 0x2c92);
            r = a - b;
        }
    }
    return r;
}
