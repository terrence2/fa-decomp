// ?NET_ReadAvail@@YAJJJ@Z @ rva 0xad540 (128 B) — v5: reuse p for d (p += 0x549e)
extern unsigned char w42D_ws0[];    /* ?ws@@3U_winsock_funcs@@A */
extern unsigned long __cdecl w42D_valP(long h);   /* validate_player */

long w42D_netReadAvail(long p1, long p2)
{
    long acc;
    long e;
    long m;
    long i;
    long p;
    long c;
    long z;
    long r;

    acc = 0;
    if (*(unsigned char *)w42D_ws0 == 0)
        goto fail;
    p = (long)w42D_valP(p1);
    if (p == 0)
        goto fail;
    i = *(long *)(p + 0x54a2);
    e = *(long *)(p + 0x549e);
    p += 0x549e;
    m = p2;
    if (i != e) {
        z = 0;
        do {
            if (acc < m) {
                if (*(char *)(p + i * 18 + 0x26) == (char)z)
                    goto latch;
                if (*(char *)(p + i * 18 + 0x27) != (char)z)
                    goto latch;
                acc += *(long *)(p + i * 18 + 0x22);
            }
latch:
            i = i + 1;
            c = *(volatile long *)(p + 8);
            if (c <= i)
                i = 0;
        } while (i != e);
    }
    r = (unsigned long)(acc < m) - 1;
    r &= m;
    return r;
fail:
    return -1;
}
