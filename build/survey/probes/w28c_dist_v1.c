// 0xc2a7c _Dist@8 (68 B) — v1: signed abs + signed max
long __stdcall w28c_dist(long *a, long *b)
{
    long dx, dy, dz;

    dx = *a - *b;
    if (dx < 0) dx = -dx;
    dy = a[1] - b[1];
    if (dy < 0) dy = -dy;
    dz = a[2] - b[2];
    if (dz < 0) dz = -dz;
    if (dy < dz) { long t = dy; dy = dz; dz = t; }
    if (dx < dy) { long t = dx; dx = dy; dy = t; }
    return dx + (dy >> 2) + (dz >> 2);
}
