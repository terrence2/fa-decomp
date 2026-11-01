// __ismbbkalnum @ rva 0xdb6a0 (18 B) — mov eax,[esp+4] / push 1 / push 0 /
//   push eax / call $FA$t_4db810 (_ismbbtype) / add esp,0xc / ret.
extern int ismbbType(int c, int mask, int flg);

int __cdecl _ismbbkalnum(int c)
{
    return ismbbType(c, 0, 1);
}