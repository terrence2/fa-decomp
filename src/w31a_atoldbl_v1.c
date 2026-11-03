/* w31A round 1: __atoldbl (rva 916976 dec, 0xdfdf0, 53 B) — plain C,
 * strgtold12 arg4 = 1 (FA: push 0x1), callee __ld12told.
 */
extern void strgtold12(void *pldb, void **ppend, char *str,
                       int f1, int f2, int f3, int f4);
extern void ld12told(void *pldb, void *x);

void _atoldbl(void *x, char *str)
{
    char *pend;
    char ldbl[12];
    strgtold12(ldbl, &pend, str, 1, 0, 0, 0);
    ld12told(ldbl, x);
}