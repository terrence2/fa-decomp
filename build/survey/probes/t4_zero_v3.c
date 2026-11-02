// t4_zero_v3: walking-pointer volatile while-form — pointer advances in the
// body (FA: add ecx,4 in the fall-through path), test through the same
// volatile pointer variable.
int IsZeroMan_x(void *p)
{
    volatile long *q = (volatile long *)p;
    int i = 0;

    while (i < 3) {
        if (*q)
            return 0;
        q = q + 1;
        i++;
    }
    return 1;
}