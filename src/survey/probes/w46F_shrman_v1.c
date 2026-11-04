/* w46F: FA rva 916064 __ShrMan (173 B, no abs fixups).
 * Signed 96-bit>>count-style shift over a 3-dword big-endian word array
 * followed by a whole-word downshift/zero pass.  FA: n=count/32 kept in
 * [esp+0x10], m=count%32 in al, mask=~(0xffffffff<<m) in [esp+0x14],
 * carry in edx, (32-m) shift count in a byte slot [esp+0x1c]. */
void __ShrMan(unsigned *p, int count)
{
    int n, m, i;
    unsigned cur, mask, carry, t;

    n = count / 32;
    m = count % 32;
    mask = ~(0xffffffffu << m);
    carry = 0;
    for (i = 0; i < 3; i++) {
        cur = p[i];
        t = cur & mask;
        p[i] = cur >> m;
        p[i] |= carry;
        carry = t << (32 - m);
    }
    for (i = 2; i >= 0; i--) {
        if (n > i)
            p[i] = 0;
        else
            p[i] = p[i - n];
    }
}