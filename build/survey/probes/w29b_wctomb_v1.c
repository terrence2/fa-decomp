// w29b F: _wctomb @ rva 0xdc600 (86 B, 9-byte prolog cbProlog: 7-byte
// cmp [0x589d88-4],0 + push esi/edi). FA body:
//   if (g1 != 0) { lockq(19); flag = 1; } else { flag = 0; g2++; }
//   r = __wctomb_lk(s, wc);   (cdecl: push wc then push s)
//   if (flag) unlockq(19); else g2--; return r;
// g1 = __nstream+0x4 (0x589d84), g2 = __nstream+0x8 (0x589d88).
extern void __cdecl lockq(int n);
extern void __cdecl unlockq(int n);
extern int __cdecl wctombLkq(char *s, unsigned short wc);
extern unsigned int gctr1;
extern unsigned int gctr2;

int wctomb_q(char *s, unsigned short wc)
{
    int r;
    int flag;
    if (gctr1 != 0) {
        lockq(19);
        flag = 1;
    } else {
        flag = 0;
        gctr2 = gctr2 + 1;
    }
    r = wctombLkq(s, wc);
    if (flag) {
        unlockq(19);
    } else {
        gctr2 = gctr2 - 1;
    }
    return r;
}