// _Octant@8 @ rva 0x11a40 — C v2 (param b read first)
char __stdcall Octantq(long *a, long *b)
{
    long dx, dy;
    char r;

    dx = b[0] - a[0];
    dy = b[2] - a[2];
    if (dx >= 0)
    {
        if (dy >= 0)
            r = (char)(dy <= dx);
        else
            r = (char)(2 + (-dy > dx));
    }
    else
    {
        if (dy >= 0)
            r = (char)(6 + (-dx < dy));
        else
            r = (char)(4 + (dy >= dx));
    }
    return r;
}
