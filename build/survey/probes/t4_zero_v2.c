// t4_zero_v2: volatile spelled inline at the load site instead of on a
// pointer local — second spelling of the same lever.
int IsZeroMan_w(void *p)
{
    int i;

    for (i = 0; i < 3; i++) {
        if (*(volatile long *)p)
            return 0;
        p = (char *)p + 4;
    }
    return 1;
}