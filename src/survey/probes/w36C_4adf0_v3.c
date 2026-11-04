/* w36C 0x4adf0 (unnamed, 48 B) v3: v1-style inlined compare (no named v local
 * -> CL keeps the loaded value in a free reg, m-first operand order 3b x?,x?
 * with m in a scratch), signed m, do-while --n latch (dec r / jnz 75).
 * FA reg plan: m=edx, best=eax (return), ptr=ecx, n=edi (4f dec), v=esi.
 * decl/init order: inits m=0 then best=0 (FA: 33 d2 before 33 c0). */
struct w36c4a {
    unsigned char pad[0x18];
    long v;
    unsigned char rest[4];
};

void *f_4adf0(struct w36c4a *ptr, long n)
{
    struct w36c4a *best;
    long m;

    m = 0;
    best = (struct w36c4a *)0;
    if (n > 0) {
        do {
            if (m < ptr->v) {
                best = ptr;
                m = ptr->v;
            }
            ptr++;
        } while (--n != 0);
    }
    return best;
}