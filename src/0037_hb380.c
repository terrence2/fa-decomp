/* rva 0xb380 (96 B) - notify: pkt_send then print, else socket_set_doa */
extern char pkt_send_you_can_play(int, char *);
extern void net_print_player_found(int, char *);
extern void socket_set_doa(unsigned int);
extern void w44f_fn2(int);
extern void w44f_fn3(int, char *, void *);
extern char w44f_str0[];

void w44F_b380(char *A, char *B)
{
    if (pkt_send_you_can_play(*(int *)A, w44f_str0)) {
        w44f_fn2(*(int *)A);
        w44f_fn3(*(int *)A, B, A + 0x24);
        net_print_player_found(*(int *)A, B);
    } else {
        socket_set_doa(*(unsigned int *)(A + 0xc));
    }
}