extern int gA;
extern int gB;

int microOrd(int x)
{
    int v[3];
    int t;

    v[0] = gA;
    v[1] = gB;
    t = v[0] + x;
    return v[2] + t;
}