/* ?NET_Disconnect@@YAXJ@Z @ rva 0xad130 (dec 708912), size 0x30 — EXACT,
 * pure C, no patches.
 *
 * C recipe: player-list entry table read at player_list_x+0x66+4*h
 * (mov eax,[eax*4+disp] with the +0x66 baked into the disp), byte-test
 * at entry+0x36, then socket_close(*(unsigned long*)e). The pointer
 * loads stay in FA's order via the simple single-exit control flow.
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_NET_Disconnect_v1.obj 708912 \
 *   --map '_player_list_x=?player_list@@3UNET_PLAYER_LIST@@A' \
 *   --map '_socket_close=?socket_close@@YAXI@Z' \
 *   build/survey/probes/w24a_NET_Disconnect_v1_fit.obj
 * (2 relocs: DIR32 player_list base + REL32 call socket_close.
 * tail = census-proven 2B filler.)
 */
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
