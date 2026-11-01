// __ismbbkprint @ rva 0xdb6c0 (18 B) — push 3 / push 0 / call _ismbbtype.
extern int ismbbType(int c, int mask, int flg);

int __cdecl _ismbbkprint(int c)
{
    return ismbbType(c, 0, 3);
}