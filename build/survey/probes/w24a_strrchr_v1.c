char *__cdecl strrchr(const char *s, int ch)
{
    const char *p;
    while (*s) s++;
    p = s;
    while (p != s - 1 && *p != (char)ch) p--;
    return (*p == (char)ch) ? (char *)p : 0;
}
