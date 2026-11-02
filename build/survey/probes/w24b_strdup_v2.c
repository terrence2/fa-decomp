/* probe v2: fpo (no pragma); p kept via if-assign shape */
extern unsigned int _strlen_a(const char *s);
extern void *_malloc_a(unsigned int n);
extern void _strcpy_a(char *d, const char *s);

char *_strdup_q(const char *src)
{
    char *p;
    if (p = (char *)_malloc_a(_strlen_a(src) + 1))
        _strcpy_a(p, src);
    return p;
}
