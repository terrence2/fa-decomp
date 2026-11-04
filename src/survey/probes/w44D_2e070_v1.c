/*
 * w44D_2e070_v1.c — @COLAddObj@0 @ 0x42e070 (128 B, fpo/esp, regs only)
 * Gates: (curThing+1 flags)&1, (curThingType+9 flags)&1.  Duplicate-scan
 * the WORD array at specials+0x4b8 (900 cap, count dword +0xe8) for the
 * WORD id _curId, else append; then iff typeFlags & 0x408000, append to
 * the WORD array at specials+0x118 (count dword +0x110, 450 cap).
 */
extern char curThing[];
extern char curThingType[];
extern char specials[];
extern unsigned short curId;

void __fastcall COLAddObj(void)
{
    int i;
    unsigned int n, n2;
    unsigned short w = curId;

    if ((*(unsigned int *)(curThing + 1) & 1) == 0)
        return;
    if ((*(unsigned int *)(curThingType + 9) & 1) == 0)
        return;
    n = *(unsigned int *)(specials + 0xe8);
    for (i = 0; i < n; i++)
        if (*(unsigned short *)(specials + 0x4b8 + i * 2) == w)
            return;
    if (n >= 900)
        return;
    *(unsigned short *)(specials + 0x4b8 + n * 2) = w;
    n++;
    *(unsigned int *)(specials + 0xe8) = n;
    if ((*(unsigned int *)(curThingType + 9) & 0x408000) != 0) {
        n2 = *(unsigned int *)(specials + 0x110);
        if (n2 >= 450)
            return;
        *(unsigned short *)(specials + 0x118 + n2 * 2) = w;
        n2++;
        *(unsigned int *)(specials + 0x110) = n2;
    }
}