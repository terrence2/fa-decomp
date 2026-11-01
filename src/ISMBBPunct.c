// __ismbbpunct @ rva 0xdb780 (18 B) — cdecl forwarder
//   ismbbType(c, 0x10, 2).
extern int ismbbType_x(int c, int flag, int type);

int ISMBBPunct_q(int c)
{
    return ismbbType_x(c, 0x10, 2);
}
