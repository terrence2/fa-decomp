// ?pkt_send_sync@@YADH@Z @ rva 0x5c7e0 (16 B) — forwarder into the next
// chunk: mov eax,[esp+4] / push 0xe / push eax / call pkt_send_type /
// add esp,8 / ret. The imm (0xe) is ARG2 and is pushed first (right-to-left)
// with the eax param-load hoisted above it: C is pkt_send_type(id, 0xe)
// (probe w13a_pktsync; first attempt with 0xe as arg1 emitted the pushes
// in the other order).
extern char __cdecl pkt_send_type(long id, long tag);

char pkt_send_sync(long id)
{
    return pkt_send_type(id, 0xe);
}