void __fastcall w32e_50a50_v1(char *p)
{
    int i;
    *(int *)p = 0;
    p += 4;
    i = 10;
    do {
        *(int *)p = -1;
        p += 0x12;
        i--;
        *(char *)(p - 0xe) = 0;
    } while (i != 0);
}