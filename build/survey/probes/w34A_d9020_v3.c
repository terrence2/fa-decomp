/* w34A_d9020 v3: byte-offset scale (FA sib [ecx+esi*1]), two-step pointer
 * chase spelled as separate statements, no ebx-touching casts.
 */
long w34A_d9020(long *a, long *t)
{
    long r, n, p;

    r = t[0];
    r += (long)a;
    n = t[1];
    if (n >= 0) {
        p = *(long *)((char *)a + n);
        r += *(long *)((char *)p + t[2]);
        r += n;
    }
    return r;
}