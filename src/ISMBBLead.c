// __ismbblead @ rva 0xdb7a0 (18 B) — cdecl forwarder
//   ismbbType(c, 0, 4).
extern int ismbbType_x(int c, int flag, int type);

int ISMBBLead_q(int c)
{
    return ismbbType_x(c, 0, 4);
}
