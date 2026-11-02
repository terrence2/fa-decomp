/* rva 907968 (0xddac0) _strpbrk 64 B -- v3: full initializer list fill */
char * __cdecl strpbrk(char *string, char *control)
{
    unsigned int map[8] = {0, 0, 0, 0, 0, 0, 0, 0};

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