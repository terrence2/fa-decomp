/* w37F v2 rva 0x20340: i declared first, id-steering variants */
extern long _fortPlayers;
extern long _fortSizeIndex;

int __stdcall w37f_20340(long id)
{
    int i;
    long *p;
    i = 0;
    p = &_fortPlayers;
    do {
        if (*p == id)
            return i;
        p++;
        i++;
    } while (p < &_fortSizeIndex);
    return -1;
}