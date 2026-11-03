// 0xd5d30 __lsearch (85 B) — v1: CRT _lsearch with inline-expanded memcpy
// (rep movsd + tail movsb) and compare(key,element) loop
extern void *memcpy(void *, const void *, unsigned int); /* intrinsic */

void *w32a_lsearch_q(void *key, void *base, unsigned int *num,
                     unsigned int width,
                     int (__cdecl *w32a_compar)(void *, void *))
{
    unsigned int i = 0;
    void *element = base;
    while (i < *num)
    {
        if (w32a_compar(key, element) == 0)
            return element;
        element = (char *)element + width;
        i++;
    }
    memcpy(element, key, width);
    ++*num;
    return element;
}