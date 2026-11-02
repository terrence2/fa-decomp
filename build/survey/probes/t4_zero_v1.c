// t4_zero_v1: volatile pointee lever. FA tests with cmp [ecx],0 (83 39 00);
// CL's non-volatile deref always materializes mov edx,[ecx]/test edx,edx
// (p_IsZeroMan_v1 = 30 B, one byte too long, jl f1 vs FA f2). A volatile
// load must be a single memory access — the test-through-memory form is
// CL's cheapest single access, so this may pin 83 39 00 directly. Pointer
// declared as a local, index walked: CL strength-reduces p[i] to *p ++
// (observed in p_IsZeroMan_v1), which is what keeps ecx walking.
int IsZeroMan_v(long *p)
{
    volatile long *q = (volatile long *)p;
    int i;

    for (i = 0; i < 3; i++)
        if (q[i])
            return 0;
    return 1;
}