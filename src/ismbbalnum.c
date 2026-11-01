// __ismbbalnum @ rva 0xdb700 (21 B) — push 1 / push 0x107 (imm32) /
//   call _ismbbtype — the 0x107 flag set needs the dword-wide push.
extern int ismbbType(int c, int mask, int flg);

int __cdecl _ismbbalnum(int c)
{
    return ismbbType(c, 0x107, 1);
}