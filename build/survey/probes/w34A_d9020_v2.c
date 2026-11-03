/* w34A_d9020 v2: byte-scaled accesses (a is a byte base: FA's sib is
 * [ecx+esi*1], and the pointer value *(long*)(a+n) is re-fetched), and
 * t[1]/n kept out of hoist range by loading after the add.
 */
long w34A_d9020(long *a, long *t)
{
    long r = t[0] + (long)a;
    long n = t[1];
    long p;

    if (n >= 0) {
        p = *(long *)((char *)a + n);
        r += *(long *)((char *)p + t[2]);
        r += n;
    }
    return r;
}