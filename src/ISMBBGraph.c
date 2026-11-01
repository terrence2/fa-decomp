// __ismbbgraph @ rva 0xdb740 (21 B) — mov eax,[esp+4] / push 3 / push
//   0x117 / push eax / call _ismbbType ($FA$_t_4db810) / add esp,0xc /
//   ret: cdecl forwarder ismbbType(c, 0x117, 3).
extern int ismbbType_x(int c, int flag, int type);

int ISMBBGraph_q(int c)
{
    return ismbbType_x(c, 0x117, 3);
}
