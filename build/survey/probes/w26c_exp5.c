// exp5: HUD convergence attempts
extern int w26_hudBright; /* map _w26_hudBright=?hudBrightness@@3JA */

/* h10: n local + S1 pre-store + if/return clamp + S3 re-store */
void __fastcall w26c_HUD_h10(unsigned char p1)
{
    int e, n;
    e = (p1 < 1) ? -16 : 16;
    n = w26_hudBright + e;
    w26_hudBright = n;
    if (n < -0x100) {
        w26_hudBright = 0xffffff00;
        return;
    }
    w26_hudBright = n;
    if (n > 0x100)
        w26_hudBright = 0x100;
}

/* h14: h5 header, if/return on global, no S3 */
void __fastcall w26c_HUD_h14(unsigned char p1)
{
    int e;
    e = (p1 < 1) ? -16 : 16;
    w26_hudBright = w26_hudBright + e;
    if (w26_hudBright < -0x100) {
        w26_hudBright = 0xffffff00;
        return;
    }
    if (w26_hudBright > 0x100)
        w26_hudBright = 0x100;
}

/* h16: h14 + duplicated self-store before 2nd if */
void __fastcall w26c_HUD_h16(unsigned char p1)
{
    int e;
    e = (p1 < 1) ? -16 : 16;
    w26_hudBright = w26_hudBright + e;
    if (w26_hudBright < -0x100) {
        w26_hudBright = 0xffffff00;
        return;
    }
    w26_hudBright = w26_hudBright;
    if (w26_hudBright > 0x100)
        w26_hudBright = 0x100;
}

/* h17: h10 without n-local (sum kept via += store + if/return + re-store) */
void __fastcall w26c_HUD_h17(unsigned char p1)
{
    int e;
    e = (p1 < 1) ? -16 : 16;
    w26_hudBright = w26_hudBright + e;
    if (w26_hudBright < -0x100) {
        w26_hudBright = 0xffffff00;
        return;
    }
    w26_hudBright = w26_hudBright + 0x10 + e - 0x10 - e;
    if (w26_hudBright > 0x100)
        w26_hudBright = 0x100;
}