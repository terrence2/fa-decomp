#pragma optimize("y", off)
void ExpandDB(char *s, char *d)
{
    unsigned short n;
    unsigned long w, v;
    n = 0x200;
    do {
        ++s;
        w = (unsigned char)s[0];
        w = w | (w << 8);
        --s;
        v = w << 16;
        w = (unsigned char)s[0];
        w = w | (w << 8);
        v = v | w;
        ++s;
        ++s;
        *(long *)d = v;
        d += 4;
        *(long *)d = v;
        d += 4;
    } while (--n);
}