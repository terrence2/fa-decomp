/* w37F v2 rva 0x91e20: char return width -> b0 01 / 32 c0 exits */
char w37f_91e20(char *p)
{
    int i;
    for (i = 0; i < 4; i++)
        if (p[i])
            return 0;
    for (i = 0; i < 6; i++)
        if (p[i + 4])
            return 0;
    return 1;
}