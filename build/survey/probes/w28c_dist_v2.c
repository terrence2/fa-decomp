// 0xc2a7c _Dist@8 — v2: pointer locals in saved regs
long __stdcall w28c_dist(long *a, long *b)
{
    long *pa, *pb;
    long dx, dy, dz, t;

    pa = a;
    pb = b;
    dx = pa[0] - pb[0];
    if (dx < 0) dx = -dx;
    dy = pa[1] - pb[1];
    if (dy < 0) dy = -dy;
    dz = pa[2] - pb[2];
    if (dz < 0) dz = -dz;
    if (dy < dz) { t = dy; dy = dz; dz = t; }
    if (dx < dy) { t = dx; dx = dy; dy = t; }
    return dx + (dy >> 2) + (dz >> 2);
}
