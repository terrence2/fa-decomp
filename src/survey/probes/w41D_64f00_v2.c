/* w41D 0x64f00 v2 — spelling variants: explicit *5<<3*9 mul chains (FA's
 * lea/shl/lea shapes) and (r*91)*2 final; int r with unsigned-div casts.
 */
extern int w41D_c90(void);   /* -> $FA$_t_464c90 */

int w41D_64f00(void)
{
    int r;
    unsigned long q;
    r = w41D_c90();
    if (r < 0) {
        q = (unsigned long)(0x167 - r) / 0x168;
        r = r + (int)((q * 5 << 3) * 9);
    }
    if (r >= 0x168) {
        q = (unsigned long)r / 0x168;
        r = r + (int)(-((q * 5 << 3) * 9));
    }
    return (r * 91) * 2;
}