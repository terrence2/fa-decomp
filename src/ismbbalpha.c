// __ismbbalpha @ rva 0xdb720 (21 B) — push 1 / push 0x103 (imm32) /
//   call _ismbbtype.
extern int ismbbType(int c, int mask, int flg);

int __cdecl _ismbbalpha(int c)
{
    return ismbbType(c, 0x103, 1);
}