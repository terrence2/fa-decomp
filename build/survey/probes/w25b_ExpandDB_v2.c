#pragma optimize("y", off)
void ExpandDB(char *s, char *d)
{
    unsigned short n = 0x200;
    unsigned short w;
    unsigned long v;
    do {
        ++s;
        w = (unsigned char)s[0];
        w = (w << 8) | w;
        --s;
        v = (w << 16) | (((unsigned char)s[0] << 8) | (unsigned char)s[0]);
        ++s;
        ++s;
        *(long *)d = v;
        d += 4;
        *(long *)d = v;
        d += 4;
    } while (--n);
}