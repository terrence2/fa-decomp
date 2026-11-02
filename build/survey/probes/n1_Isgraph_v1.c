// n1 Isgraph: Ispunct recipe (tier1_a_r5) generalized to mask 0x117.
extern char ctype204[];
extern unsigned short *_pctype;
extern int __cdecl _isctype(int c, int mask);

int __cdecl isgraph_q(int c)
{
    if (*(int *)ctype204 > 1)
        return _isctype(c, 0x117);
    return _pctype[c] & 0x117;
}
