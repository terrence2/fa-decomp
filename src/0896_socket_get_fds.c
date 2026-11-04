/* w35B: ?socket_get_fds@@YAXPAUfd_set@@00@Z @ rva 0xa34f0 (64 B)
 * FA: eax=[esp+4](r); push imm(socket_list+0x8); push eax; call
 * $FA$_t_4a3530 (cdecl, caller cleans); eax=[esp+0x10] (w, re-read AFTER the
 * call — esp still -8); add esp,8; push imm(+0x210); push eax; call;
 * eax=[esp+0x14] (e); add esp,8; push imm(+0x10c); push eax; call; add
 * esp,8; ret; pad 8bff+8da42400000000 (9 B).
 * Imm args are socket_list interior pointers -> extern arrays w/ map +delta.
 */
extern void sgf_h(void *p, void *lst);      /* $FA$_t_4a3530 */
extern unsigned char sgf_a8[];      /* ?socket_list@@3USOCKET_STATE_LIST@@A+0x8 */
extern unsigned char sgf_w210[];    /* ?socket_list@@3USOCKET_STATE_LIST@@A+0x210 */
extern unsigned char sgf_e10c[];    /* ?socket_list@@3USOCKET_STATE_LIST@@A+0x10c */

void __cdecl socket_get_fds(void *r, void *w, void *e)
{
    sgf_h(r, sgf_a8);
    sgf_h(w, sgf_w210);
    sgf_h(e, sgf_e10c);
}