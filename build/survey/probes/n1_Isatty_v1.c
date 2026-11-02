// n1 Isatty v1: signed fh (sar grp), mixed-type unsigned range test (jb),
// scale-1 fhLockBase row load, byte osfile test.
extern long _nhandle;
extern char fhLockBase[];

int __cdecl _isatty_q(int fh)
{
    int idx, grp;
    char *row;
    if ((unsigned long)fh >= (unsigned long)_nhandle)
        return 0;
    idx = (fh & 0x1f) << 2;
    grp = (fh & ~0x18) >> 3;
    row = *(char **)((char *)fhLockBase + grp);
    return row[idx + 4] & 0x40;
}
