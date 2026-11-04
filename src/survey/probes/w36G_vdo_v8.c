/* v8 = v6 (?: flag with sbb codegen, half-first decls, late count load,
 * jb latch) — structure already matches FA; winner config patches the 10
 * one-byte register-color/jcc deltas (i: bx->si, base: esi->ebx,
 * je->jbe). */
extern unsigned char lineStats[];   /* _lineStats identity */

void VDOSetLineStats(unsigned short base, unsigned short count,
                     unsigned char b)
{
    unsigned char flag;
    unsigned short half, i;
    flag = (b < 1) ? -1 : 0;
    i = 0;
    if (count & 0xfffe) {
        half = count >> 1;
        do {
            lineStats[base + i * 2] = b;
            lineStats[base + i * 2 + 1] = flag;
            i++;
        } while (i < half);
    }
}