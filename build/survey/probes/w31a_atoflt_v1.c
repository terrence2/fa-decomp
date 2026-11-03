/* w31A round 1: __atoflt (rva 917040 dec, 0xdfe30, 53 B) — plain C,
 * strgtold12 arg4 = 0, callee __ld12tof.
 */
extern void strgtold12(void *pldb, void **ppend, char *str,
                       int f1, int f2, int f3, int f4);
extern void ld12tof(void *pldb, void *x);

void _atoflt(void *x, char *str)
{
    char *pend;
    char ldbl[12];
    strgtold12(ldbl, &pend, str, 0, 0, 0, 0);
    ld12tof(ldbl, x);
}