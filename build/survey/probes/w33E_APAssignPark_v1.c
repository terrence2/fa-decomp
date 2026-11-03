/* FA chunk _APAssignPark@0 rva 0xb97c0 (112 B) — wave 33 batch E probe v1.
   Assigns curId into the current thing's park slot table; scans slot words
   from +0x111 for the first zero. FA loads the thing pointer (0x508969 =
   _curThing+0x231) afresh at every use and re-sign-extends the slot count
   inside the loop (no CSE). */
extern int __stdcall APGetPark(void);
extern void __stdcall APUnassignPark(void);
extern void *thp;      /* lives at _curThing+0x231 (0x508969) */
extern short curId;    /* 0x4f2f24 */

int __stdcall APAssignPark(void)
{
    int i;
    short cnt;
    if (thp == 0)
        return -1;
    {
        int park;
        park = APGetPark();
        if (park != -1)
            return park;
    }
    APUnassignPark();
    i = 0;
    cnt = *(short *)((char *)thp + 0xe0);
    {
        short *w = (short *)((char *)thp + 0x111);
        while ((int)cnt > i)
        {
            if (*w == 0)
                goto found;
            w++;
            i++;
        }
    }
    return -1;
found:
    *(short *)((char *)thp + 0x111 + i * 2) = curId;
    return i;
}