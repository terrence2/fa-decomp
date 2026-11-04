// ?socket_flush_close@@YAXI@Z @ rva 0xa2e30 (16 B) — cdecl stack-param thunk:
// mov eax,[esp+4]/push 1/push eax/call helper($FA$_t_4a2e50, argclean 8)/ret.
// Fetch-param-before-push-constant from plain right-to-left C (probe
// w13b_socketflush).
extern void socketCloseX_(unsigned long s, int how);

void socket_flush_close(unsigned long s)
{
    socketCloseX_(s, 1);
}