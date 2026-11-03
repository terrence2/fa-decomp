/* w34A_d9020 v5: first param as char * (FA's sib is [ecx+esi*1] = byte
 * offset); chase through a p local, sequential statements.
 */
long w34A_d9020_v5(char *a, long *t)
{
    long r, n, p;

    r = t[0];
    r += (long)a;
    n = t[1];
    if (n >= 0) {
        p = *(long *)(a + n);
        r += *(long *)(p + t[2]);
        r += n;
    }
    return r;
}