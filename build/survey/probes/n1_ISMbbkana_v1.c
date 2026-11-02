// n1 ISMbbkana: cmp [__mbctype+0x104],932 mem-compare + _ismbbType(c,0,3),
// shared xor-exit. _mbcFlag maps to __mbctype+0x104 (baked addend in map TO).
extern char mbcFlag[];
extern int __cdecl ismbbType(int c, int mask, int flg);

int __cdecl _ismbbkana_q(unsigned int c)
{
    if (*(int *)mbcFlag == 0x3a4)
        if (ismbbType((int)c, 0, 3))
            return 1;
    return 0;
}
