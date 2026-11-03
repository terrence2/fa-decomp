/* FA chunk ?NET_Flush@@YADJD@Z rva 0xad270 (80 B) — wave 33 batch E probe v1.
   Validates the player id, then calls the flush routine with the queue
   pointer (thing + 0x287e) and the id; on a false flush result runs the
   dead-air handler. FA's flush callee is the anonymous chunk at 0x4ae200
   (still a stub; map _flushq=$FA$_t_4ae200). */
struct _winsock_funcs { char b0; };
extern struct _winsock_funcs ws;   /* byte 0 read via a0 moffs */

struct _player_info { char pad[0x287e]; int cnt; char pad2[0x100]; };
extern struct _player_info *validate_player(long id);

extern "C" char __cdecl flushq(char *q, long id);
void socket_process_doa(void);

char __cdecl NET_Flush(unsigned long id, char flags)
{
    char r;
    struct _player_info *pi;
    char *q;
    if (!ws.b0)
        return 0;
    pi = validate_player(id);
    if (pi == 0)
        return 0;
    q = (char *)pi + 0x287e;
    if (*(int *)((char *)pi + 0x287e) <= 0)
        return 1;
    r = flushq(q, id);
    if (r == 0)
        socket_process_doa();
    return r;
}