/* FA chunk ?NET_Flush@@YADJD@Z rva 0xad270 (80 B) — wave 33 batch E probe v2.
   v1 used inline returns; FA reuses shared trailing exit blocks reached by
   2-byte je/jle. Spell with gotos so CL shares the exits. cnt field is a
   DWORD int at +0x287e. flushq is the anonymous 0xae200 chunk (fastcall,
   still stubbed, flushes 8-byte records). */
struct _winsock_funcs { char b0; };
extern struct _winsock_funcs ws;
struct _player_info { char pad[0x287e]; int cnt; };

extern struct _player_info *validate_player(long id);
extern "C" char __cdecl flushq(char *q, long id);
extern void __cdecl socket_process_doa(void);

char __cdecl NET_Flush(unsigned long id, char flags)
{
    struct _player_info *pi;
    char r;
    if (!ws.b0)
        goto ret0;
    pi = validate_player((long)id);
    if (pi == 0)
        goto ret0;
    if ((int)pi->cnt <= 0)
        goto ok1;
    r = flushq((char *)pi + 0x287e, id);
    if (r == 0)
        socket_process_doa();
    return r;
ok1:
    return 1;
ret0:
    return 0;
}