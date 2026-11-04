/* w37E candidate 0x9da70 v2: guard flipped to >=0x3c/return-1 so CL inlines
   the return-1 arm and leaves the write block out-of-line (FA: cmp/jl,
   mov eax,1 ret, dup-ret, write). */
extern short numPlanes;
extern short planes[];
extern short curId;
long PLANEAddProc(void)
{
    short *p = planes;
    short *e = planes + numPlanes;
    while (p < e) {
        if (*p == curId)
            return 0;
        p++;
    }
    if (numPlanes >= 0x3c)
        return 1;
    *e = curId;
    numPlanes++;
    return 0;
}