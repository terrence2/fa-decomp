/* w34A_d9020 v4: no p local — nested deref spelled inline so CL keeps
 * the chase in ecx/edx without extra scratch.
 */
long w34A_d9020(long *a, long *t)
{
    long r, n;

    r = t[0];
    r += (long)a;
    n = t[1];
    if (n >= 0) {
        r += *(long *)((char *)*(long *)((char *)a + n) + t[2]);
        r += n;
    }
    return r;
}