/* rva 907968 (0xddac0) _strpbrk 64 B  -- v2: byte map + byte fill loop */
char * __cdecl strpbrk(char *string, char *control)
{
    unsigned char map[32];
    int count;

    for (count = 0; count < 32; count++)
        map[count] = 0;

    while (*control) {
        map[*control >> 3] |= 1 << (*control & 7);
        control++;
    }

    while (*string) {
        if (map[*string >> 3] & (1 << (*string & 7)))
            return string;
        string++;
    }

    return 0;
}