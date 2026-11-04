/* FA 0x12160 BoxAnd@12 (176 B) v2: short regs only, width/height via (short)(max(int...)) - short */
unsigned char __stdcall w43E_BoxAndQ(short *out, short *a, short *b)
{
    short ax, cx, bp, m, n, width, height;
    int bw, aw, bh, ah;

    bp = b[0];
    cx = a[0];
    ax = (bp > cx) ? bp : cx;
    bw = (int)b[2] + (int)bp;
    aw = (int)a[2] + (int)cx;
    out[0] = ax;
    width = (short)(aw > bw ? aw : bw) - ax;
    bp = b[1];
    cx = a[1];
    ax = (bp > cx) ? bp : cx;
    out[2] = width;
    bh = (int)b[3] + (int)bp;
    ah = (int)a[3] + (int)cx;
    out[1] = ax;
    height = (short)(bh > ah ? bh : ah) - ax;
    out[3] = height;
    if (width <= 0 || height <= 0) {
        out[0] = 0;
        out[3] = 0;
        out[2] = 0;
        out[1] = 0;
        return 0;
    }
    return 1;
}