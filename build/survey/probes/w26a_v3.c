#include <string.h>
extern int __cdecl isspace(int c);
long vi_s1(unsigned char *s)
{
    long r;
    if (isspace(*s)) { do { ++s; } while (isspace(*s)); }
    r = (*s == '/');
    return r;
}
long vi_s2(char *s)
{
    char c;
    if (isspace(*s)) { do { ++s; } while (isspace(*s)); }
    c = *(char*)s;
    return (unsigned char)(c == '/');
}
int vf_s1(unsigned char *p, int d) { return p[1] < d; }
int vf_s2(unsigned char *p, int d) { return (int)p[1] < d; }
int vf_s3(int p, int d) { return *(unsigned char *)(p + 1) < d; }
