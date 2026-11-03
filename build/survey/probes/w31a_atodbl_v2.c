/* w31A round 1: __atodbl variant 2 — ldbl first (alt decl order).
 */
extern void strgtold12(void *pldb, void **ppend, char *str,
                       int f1, int f2, int f3, int f4);
extern void ld12tod(void *pldb, void *x);

void _atodbl(void *x, char *str)
{
    char ldbl[12];
    char *pend;
    strgtold12(ldbl, &pend, str, 0, 0, 0, 0);
    ld12tod(ldbl, x);
}