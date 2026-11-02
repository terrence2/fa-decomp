/* probe v1: ebp prolog + mov edi,[ebp+8] + push/strlen/pop edx/inc/push/malloc
   or eax,eax; je; strcpy; pop edx x2; pop edi; leave */
#pragma optimize("y", off)
extern unsigned int _strlen_a(const char *s);      /* obj __strlen_a -> _strlen */
extern void *_malloc_a(unsigned int n);            /* obj __malloc_a -> _malloc */
extern void _strcpy_a(char *d, const char *s);     /* obj __strcpy_a -> _strcpy */

char *_strdup_q(const char *src)
{
    char *p;
    p = (char *)_malloc_a(_strlen_a(src) + 1);
    if (p != 0)
        _strcpy_a(p, src);
    return p;
}
