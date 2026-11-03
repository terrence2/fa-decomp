extern void *MP_Info(void);
extern int numComputers;
extern unsigned char packetBytes[];

char __stdcall MPPaused(void)
{
    int i;
    void *mp;

    if (numComputers == 1)
        return 0;
    i = 0;
    while (i < numComputers) {
        mp = MP_Info();
        if (*(int *)((char *)mp + 0x158) & (1 << i))
            if (packetBytes[i])
                return 1;
        i++;
    }
    return 0;
}