/* w31A round 1 WINNER (kept as final): __atodbl (rva 916912 dec,
 * 0xdfdb0, 53 B) — plain C reproduces FA byte-exactly on first try.
 * Recipe: extern cdecl strgtold12(void* ldbl12, void** pend, char* str,
 * int,int,int,int) + ld12tod(void*,void*); locals void* pend (S+0) and
 * char ldbl[12] (S+4) — 16 B FPO frame, params (x, str).
 */
extern void strgtold12(void *pldb, void **ppend, char *str,
                       int f1, int f2, int f3, int f4);
extern void ld12tod(void *pldb, void *x);

void _atodbl(void *x, char *str)
{
    char *pend;
    char ldbl[12];
    strgtold12(ldbl, &pend, str, 0, 0, 0, 0);
    ld12tod(ldbl, x);
}