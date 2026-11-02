/* probe v3: like v1 but single-expression chain ordering forced by temps */
#pragma optimize("y", off)
extern unsigned int _strlen_a(const char *s);
extern void *_malloc_a(unsigned int n);
extern void _strcpy_a(char *d, const char *s);

char *_strdup_q(const char *src)
{
    char *p = (char *)_malloc_a(_strlen_a(src) + 1);
    return p ? (_strcpy_a(p, src), p) : p;
}
