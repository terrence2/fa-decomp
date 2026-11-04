/* _GRPPart@12 @ rva 0x5ea70 (128 B) v4: unsigned n + sbb-ternary return
   (2 + ((n<1) ? -1 : 0)) to get FA's cmp $1 / sbb / add $2 tail */
extern unsigned char wingSizes[];   /* -> _wingSizes (0x5421b0) */
extern unsigned char wingIds[];     /* -> _groupIds (0x5420e8) */

char __stdcall GRPPart(short part, int *p1, int *p2)
{
    unsigned long n;
    long g;
    long off;
    short *p;

    for (off = 0, g = 0; off < 100; off += 10, g++) {
        n = wingSizes[g];
        if ((long)--n >= 0) {
            p = (short *)&wingIds[2 * (off + n)];
            do {
                if (*p == part) {
                    if (p1 != 0) *p1 = g;
                    if (p2 != 0) *p2 = n;
                    return (char)(2 + ((n < 1) ? -1 : 0));
                }
                p--;
                n--;
            } while ((long)n >= 0);
        }
    }
    if (p1 != 0) *p1 = -1;
    if (p2 != 0) *p2 = -1;
    return 0;
}