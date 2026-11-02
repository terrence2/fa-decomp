#pragma optimize("y", off)
int QuickDist(int *a, int *b)
{
    int *pa, *pb;
    int d0, d1, d2;
    pa = a;
    pb = b;
    d0 = *pa - *pb;
    if (d0 < 0) d0 = -d0;
    d1 = pa[1] - pb[1];
    if (d1 < 0) d1 = -d1;
    d2 = pa[2] - pb[2];
    if (d2 < 0) d2 = -d2;
    return d0 + d1 + d2;
}