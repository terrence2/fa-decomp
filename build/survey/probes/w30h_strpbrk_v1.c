/* rva 907968 (0xddac0) _strpbrk 64 B
 * 8x push eax zeroed map on stack; bts/bt scans */
char * __cdecl strpbrk(char *string, char *control)
{
    unsigned int map[8];
    int count;

    for (count = 0; count < 8; count++)
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