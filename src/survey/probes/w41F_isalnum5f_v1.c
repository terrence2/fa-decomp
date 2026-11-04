// w41F unnamed 0x4d4370 (71 B): _isalnum + '_' identifier-char variant
// (sibling of w41F_isalpha5f, mask 0x107).
extern char ctype204[];
extern unsigned short *_pctype;
extern int __cdecl _isctype(int c, int mask);

int __cdecl isalnum_5f(int c)
{
    int r;
    if (*(int *)ctype204 > 1)
        r = _isctype(c, 0x107);
    else
        r = _pctype[c] & 0x107;
    if (r != 0) return 1;
    if (c == 0x5f) return 1;
    return 0;
}