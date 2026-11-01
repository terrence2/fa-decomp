// ?socket_set_socket@@YAXPAUsocket_state@@I@Z @ rva 0xa3150 (16 B, FPO
// fpo/esp params=2 dwords) — stores the socket handle at +0xc then
// tail-jumps $FA$_t_4a31e0 (same init tail as socket_set_state; FA's reg
// plan picks eax/ecx the opposite way round from _state — probe decides
// C vs asm).
extern void __fastcall socketSetSocketTail(void);
struct socket_state;
void socket_set_socket(struct socket_state *p, unsigned s)
{
    ((unsigned *)p)[3] = s;
    socketSetSocketTail();
}