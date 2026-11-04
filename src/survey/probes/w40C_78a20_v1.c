/* wave-40C probe v1: MatchPattern (0x78a20, 128 B) */
int _strnicmp(const char *, const char *, int);

char MatchPattern(char *s1, char *s2)
{
    char *p, *t;

    p = s1;
    t = s2;
    while (*p) {
        if (*t == 0)
            break;
        if (*p == '?') {
            p++;
            t++;
        } else if (*p == '*') {
            p++;
            if (*t) {
                do {
                    if (_strnicmp(p, t, 1) == 0)
                        break;
                    t++;
                } while (*t);
            }
        } else {
            if (_strnicmp(p, t, 1))
                return 0;
            p++;
            t++;
        }
    }
    if (*p)
        return 0;
    if (*t)
        return 0;
    return 1;
}