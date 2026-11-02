#pragma optimize("y", off)
int __stdcall QuickDist(int *a, int *b)
{
    int d0, d1, d2;
    d0 = a[0] - b[0];
    if (d0 < 0) d0 = -d0;
    d1 = a[1] - b[1];
    if (d1 < 0) d1 = -d1;
    d2 = a[2] - b[2];
    if (d2 < 0) d2 = -d2;
    return d0 + d1 + d2;
}