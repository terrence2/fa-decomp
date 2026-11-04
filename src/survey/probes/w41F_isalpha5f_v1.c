// w41F unnamed 0x4d4320 (71 B): _isalpha + '_' identifier-char variant.
// N-band Isctype 4-patch family with an extra (c == 0x5f) accept check:
// FA loads c into esi in both branches and the bool tail compares esi.
extern char ctype204[];
extern unsigned short *_pctype;
extern int __cdecl _isctype(int c, int mask);

int __cdecl isalpha_5f(int c)
{
    int r;
    if (*(int *)ctype204 > 1)
        r = _isctype(c, 0x103);
    else
        r = _pctype[c] & 0x103;
    if (r != 0) return 1;
    if (c == 0x5f) return 1;
    return 0;
}