// ?pkt_build_sync_reply@@YAXPAUNET_PKT@@@Z @ rva 0x5cd90 (32 B) — FA asm:
//   mov eax,[esp+4] / push 0xf / push eax / push 0xffffffff /
//   call pkt_set_header / add esp,0xc / ret
// Sibling of pkt_build_sync with TYPE 0xf (probe b18c_pkt_build_sync_reply).
extern void __cdecl pkt_set_header(int a, char *pkt, int b);

void __cdecl pkt_build_sync_reply(char *pkt)
{
    pkt_set_header(-1, pkt, 0xf);
}
