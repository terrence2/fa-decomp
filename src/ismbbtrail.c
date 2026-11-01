// __ismbbtrail @ rva 0xdb7c0 (18 B) — push 8 / push 0 / call _ismbbtype.
extern int ismbbType(int c, int mask, int flg);

int __cdecl _ismbbtrail(int c)
{
    return ismbbType(c, 0, 8);
}