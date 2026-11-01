// ?pkt_build_sync@@YAXPAUNET_PKT@@@Z @ rva 0x5cd70 (32 B) — FA asm:
//   mov eax,[esp+4] / push 0xe / push eax / push 0xffffffff /
//   call pkt_set_header / add esp,0xc / ret
// pkt_set_header(-1, pkt, 0xe): right-to-left push order — 0xe lands as the
// third arg (the pkt TYPE word written to [pkt] and [pkt+2]=type+4), -1 as
// unused first arg. Plain C exact (probe b18c_pkt_build_sync). One of three
// consecutive NET-fill siblings sharing one shape (sync 0xe / reply 0xf /
// play_game 0xd).
extern void __cdecl pkt_set_header(int a, char *pkt, int b);

void __cdecl pkt_build_sync(char *pkt)
{
    pkt_set_header(-1, pkt, 0xe);
}
