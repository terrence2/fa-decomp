extern unsigned long __cdecl validate_player(long h);
extern unsigned char ws_x[];

long __cdecl NET_WriteAvail(long h)
{
    unsigned long p;
    if (!*(unsigned char *)ws_x)
        goto fail;
    p = (unsigned long)validate_player(h);
    if (!p)
        goto fail;
    return *(long *)((char *)p + 0x2c8e) - *(long *)((char *)p + 0x2c92);
fail:
    return 0;
}
