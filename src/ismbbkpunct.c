// __ismbbkpunct @ rva 0xdb6e0 (18 B) — push 2 / push 0 / call _ismbbtype.
extern int ismbbType(int c, int mask, int flg);

int __cdecl _ismbbkpunct(int c)
{
    return ismbbType(c, 0, 2);
}