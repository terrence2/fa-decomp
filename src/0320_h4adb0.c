/* wave-40C probe v1: unnamed 0x4adb0 (64 B) - best-candidate selection loop */
typedef struct {
    int f[6];      /* +0x00..0x14 */
    int a18;       /* +0x18 */
    int b1c;       /* +0x1c */
} S40X;

int w40x_best4adb0(S40X *a1, int a2)
{
    S40X *p, *best;
    int t, c, d, i;

    best = 0;
    t = 0;
    i = a2;
    if (i > 0) {
        do {
            c = a1->b1c;
            if (c > t) {
                d = a1->a18;
                if (d > 0) {
                    best = a1;
                    t = c;
                }
            }
            a1 += 1;
        } while (--i);
    }
    return (int)best;
}