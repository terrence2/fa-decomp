extern void __cdecl net_write_output_q(int h);
extern void __cdecl socket_build_write_fds(void);
extern unsigned char player_list_x[];

void __cdecl net_handle_fd_write(void *s)
{
    long h = *(long *)s;
    unsigned long e;
    if (h == -1)
        goto tail;
    e = *(unsigned long *)(player_list_x + 0x66 + 4 * h);
    if (*(long *)((char *)e + 0x2c92) <= 0)
        goto tail;
    net_write_output_q(h);
    return;
tail:
    socket_build_write_fds();
}
