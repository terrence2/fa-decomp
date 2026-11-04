// probe w45D_atohb (FA 0x41e380, 160B): hex-pair decoder -> ?atohb@@YADPADPAEH@Z
char atohb(char *str, unsigned char *out, int i)
{
    unsigned char hi, lo;
    while (i > 0) {
        hi = *str;
        if (hi == 0)
            break;
        if (hi >= 0x30 && hi <= 0x39)
            hi = hi - 0x30;
        else if (hi >= 0x41 && hi <= 0x46)
            hi = hi - 0x37;
        else if (hi >= 0x61 && hi <= 0x66)
            hi = hi - 0x57;
        else
            return 0;
        lo = str[1];
        str++;
        i--;
        if (lo == 0)
            return 0;
        hi <<= 4;
        if (lo >= 0x30 && lo <= 0x39)
            lo = lo - 0x30;
        else if (lo >= 0x41 && lo <= 0x46)
            lo = lo - 0x37;
        else if (lo >= 0x61 && lo <= 0x66)
            lo = lo - 0x57;
        else
            return 0;
        hi = hi | lo;
        str++;
        *out = hi;
        i--;
        out++;
    }
    return i == 0;
}