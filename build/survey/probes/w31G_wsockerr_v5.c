/* v5: tmp-free reuse probe — inner args spelled via the pushed-arg slots */
extern char *(*w31g_wsf)(char *, int, char *, int);
extern char *w31g_wproc(int, char *, char *, int);

char *__cdecl w31g_wsockerr(char *a1, int a2, char *a3, int a4)
{
    char *r;
    r = w31g_wsf(a1, a2, a3, a4);
    return w31g_wproc(r, a1, a2, a3, a4);
}
