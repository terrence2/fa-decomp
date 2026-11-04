// ?socket_close@@YAXI@Z @ rva 0xa2e40 (16 B) — same thunk shape as
// socket_flush_close but passes 0 (probe w13b_socketclose).
extern void socketCloseX_(unsigned long s, int how);

void socket_close(unsigned long s)
{
    socketCloseX_(s, 0);
}