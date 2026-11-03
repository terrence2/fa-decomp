/* v7: whole-body patch fallback — CL 4.2 re-pushes both calls' args
 * (8 pushes), FA shares the 4 inner-call slots with the outer's args 2..5;
 * no C spelling reuses them, so the body is the FA bytes with the two
 * call sites attached as newsite relocs. */
extern char *(*w31g_wsf)(char *, int, char *, int);
extern char *w31g_wproc(int, char *, char *, int);

char *__cdecl w31g_wsockerr(char *a1, int a2, char *a3, int a4)
{
    return w31g_wproc(w31g_wsf(a1, a2, a3, a4), a1, a2, a3, a4);
}
