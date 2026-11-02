// n1 Isalnum: Ispunct recipe (tier1_a_r5) generalized to mask 0x107.
extern char ctype204[];
extern unsigned short *_pctype;
extern int __cdecl _isctype(int c, int mask);

int __cdecl isalnum_q(int c)
{
    if (*(int *)ctype204 > 1)
        return _isctype(c, 0x107);
    return _pctype[c] & 0x107;
}
