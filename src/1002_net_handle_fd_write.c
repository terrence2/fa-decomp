/* ?net_handle_fd_write@@YAXPAUsocket_state@@@Z @ rva 0xadf80 (dec 712576),
 * size 0x30 — EXACT, pure C, no patches.
 *
 * C recipe: goto-tail shape makes CL keep FA's two forward branches
 * (je/jle to the common socket_build_write_fds tail call), the call +
 * immediate ret, and the final jmp to the writer routine with the
 * matching jcxz-free byte order. Single-exit with the tail call last.
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_net_handle_fd_write_v2.obj 712576 \
 *   --map '_player_list_x=?player_list@@3UNET_PLAYER_LIST@@A' \
 *   --map '_net_write_output_q=?net_write_output_q@@YAXH@Z' \
 *   --map '_socket_build_write_fds=?socket_build_write_fds@@YAXXZ' \
 *   build/survey/probes/w24a_net_handle_fd_write_v2_fit.obj
 * (3 relocs: DIR32 player_list base + REL32 call net_write_output_q +
 * REL32 jmp socket_build_write_fds. tail = census-proven filler
 * 05 00 00 00 00.)
 */
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
