// _PointInBox@8 @ rva 0x11f00 — C v1
struct PT2 { short x, y; };
struct BOX4 { short x0, y0, w, h; };

char __stdcall PointInBoxq(struct PT2 *p, struct BOX4 *box)
{
    if (box->x0 > p->x)
        return 0;
    if (box->y0 > p->y)
        return 0;
    if (box->x0 + box->w <= p->x)
        return 0;
    if (box->y0 + box->h <= p->y)
        return 0;
    return 1;
}
