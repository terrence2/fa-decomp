extern void __cdecl socket_close(unsigned h);
extern unsigned char player_list_x[];

void __cdecl NET_Disconnect(long h)
{
    unsigned long e = *(unsigned long *)(player_list_x + 0x66 + 4 * h);
    if (e) {
        if (*(unsigned char *)(e + 0x36))
            socket_close(*(unsigned long *)e);
    }
}
