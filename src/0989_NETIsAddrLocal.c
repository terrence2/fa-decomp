// 0xad6b0 ?NETIsAddrLocal@@YADPAUNET_ADDRESS@@@Z (64 B) — v2 (if-block guard
// so the jle targets the shared tail return; decl order swapped for reg plan)
extern char __cdecl net_addr_equal27(char *a, char *b);
extern char *proto_ptr27;

char __cdecl NETIsAddrLocal27(char *addr)
{
    long cnt;
    char *ad;

    cnt = *(long *)(proto_ptr27 + 0xc);
    ad = (char *)proto_ptr27 + 0x10;
    if (cnt > 0) {
        do {
            cnt = cnt - 1;
            if (net_addr_equal27(ad, addr))
                return 1;
            ad = ad + 0xe;
        } while (cnt != 0);
    }
    return 0;
}
