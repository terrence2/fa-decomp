extern unsigned long __cdecl validate_player(long h);
extern unsigned char ws_x[];

long __cdecl NET_WriteAvail(long h)
{
    if (!*(unsigned char *)ws_x)
        return 0;
    {
        unsigned long p = (unsigned long)validate_player(h);
        if (!p)
            return 0;
        return *(long *)((char *)p + 0x2c8e) - *(long *)((char *)p + 0x2c92);
    }
}
