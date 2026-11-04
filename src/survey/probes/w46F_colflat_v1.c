/* w46F: FA rva 186576 ?COLFlatGround@@YIDJPAUF24_POINT3@@00@Z (192 B).
 * __fastcall(int limAdj, F24_POINT3 *p, F24_POINT3 *a, F24_POINT3 *out)->char.
 * lim = ecx - *(int*)(_specials+0x4ac); y0 = p->y tested twice against lim;
 * dy-scaled interpolation of a toward p clamped at lim, else out=*p clamp. */
extern unsigned char _specials[];

typedef struct { int x, y, z; } F24_POINT3;

char __fastcall COLFlatGround(int c1, F24_POINT3 *p, F24_POINT3 *a, F24_POINT3 *b)
{
    int lim, y0, dx, dy;

    lim = c1 - *(int *)(_specials + 0x4ac);
    y0 = p->y;
    if (y0 < lim)
        goto copyout;
    if (a->y >= lim)
        return 0;
    if (y0 < lim)
        goto copyout;
    dx = lim - y0;
    dy = a->y - y0;
    if (dx < 0) {
        dx = -dx;
        dy = -dy;
    }
    while (dx > 200 || dy > 200) {
        dx >>= 1;
        dy >>= 1;
    }
    if (dy != 0) {
        b->x = p->x + (a->x - p->x) * dx / dy;
        b->y = lim;
        b->z = p->z + (a->z - p->z) * dx / dy;
        return 1;
    }
copyout:
    *b = *p;
    if (b->y < lim)
        b->y = lim;
    return 1;
}