// __ismbbprint @ rva 0xdb760 (21 B) — cdecl forwarder
//   ismbbType(c, 0x157, 3) (cf. __ismbbgraph).
extern int ismbbType_x(int c, int flag, int type);

int ISMBBPrint_q(int c)
{
    return ismbbType_x(c, 0x157, 3);
}
