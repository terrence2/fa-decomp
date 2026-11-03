extern int w32e_getval(void);

int w32e_64e50_v1(void)
{
    int v = w32e_getval();
    if (v > 90)
        v = 90;
    if (v < -90)
        v = -90;
    return v * 182;
}