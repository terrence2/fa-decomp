// n1 Islower: Ispunct recipe (tier1_a_r5) generalized to mask 0x2.
extern char ctype204[];
extern unsigned short *_pctype;
extern int __cdecl _isctype(int c, int mask);

int __cdecl islower_q(int c)
{
    if (*(int *)ctype204 > 1)
        return _isctype(c, 0x2);
    return _pctype[c] & 0x2;
}
