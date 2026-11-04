/* w42A_zap_v2.c — v2: decl/statement order i-first (FA: 33 c9 i; ba p) */
extern long fortPlayers[];
extern long fortSizeIndex;

long __stdcall w42A_zap(long id)
{
    long i;
    long *p;

    i = 0;
    p = fortPlayers;
    for (;;) {
        if (*p == id) {
            fortPlayers[i] = -1;
            return id;
        }
        p++;
        i++;
        if (p >= (long *)&fortSizeIndex)
            return id;
    }
}