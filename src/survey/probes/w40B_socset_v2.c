/* rva 0xa3170 (dec 668016), 80 B socket_set_all_players_state_funcs.
 * v2: counter n declared FIRST (FA xor edx is the first instr after push ebx),
 * count pre-loaded into local i (FA a1-load), f/state hoisted after the
 * exit check (FA loads them post-jle), je-chain via goto for the shared
 * loop-bottom, id as a fresh local (FA: edi).
 */
extern long w40b_socnum;   /* -> ?socket_list@@3USOCKET_STATE_LIST@@A */
extern long w40b_socarr;   /* -> ?socket_list@@3USOCKET_STATE_LIST@@A+0x424 */
extern long w40b_plist;    /* -> ?player_list@@3UNET_PLAYER_LIST@@A+0x18 */

void socset0(long f, long state, long flags)
{
    long n = 0;
    char *e = (char *)&w40b_socarr;
    long i = w40b_socnum;
    long ff, st;

    if (i <= 0)
        return;
    ff = f;
    st = state;
    do {
        long id;
        if (*(unsigned char *)(e + 0x18) == 0)
            goto next;
        id = *(long *)e;
        if (id == -1)
            goto next;
        if (w40b_plist == id)
            goto next;
        *(long *)(e + 0x1c) = ff;
        *(long *)(e + 0x10) = st;
next:
        n++;
        e += 0x32;
    } while (n < w40b_socnum);
}