/*
 * w44D_51390_v1.c — @FMBrakes@8 @ 0x451390 (136 B, fpo/esp)
 * Fastcall dword,dword params (tests: cl, dl).  Guard flags & 4 at
 * curThing+0x160 sets (or 0x80) / clears (~0x80) bit 0x80 and stamps
 * currentT+0xc into curThing+0x270; then (flags & 0x80) picks a
 * sound-table pointer via nested OnTheGround ternary and fires a
 * 15-arg stdcall SoundOn (curId pushed full-reg ecx, -1 last).
 */
extern char curThing[];
extern unsigned short currentT;
extern unsigned short curId;
extern char pmapCalled[];
extern char __stdcall OnTheGround(void);
extern char __stdcall SoundOn(char *msg, short a1, short a2, char a3,
    unsigned short a4, short a5, short a6, char a7, short a8, short a9,
    unsigned short a10, unsigned short a11, short a12, unsigned char a13,
    short a14);

void __fastcall FMBrakes(unsigned long x, unsigned long y)
{
    char *snd;

    if (*(unsigned int *)(curThing + 0x160) & 4)
        return;
    if ((unsigned char)x != 0) {
        *(unsigned int *)(curThing + 0x160) |= 0x80;
        *(unsigned short *)(curThing + 0x270) = currentT + 0xc;
    } else {
        *(unsigned int *)(curThing + 0x160) =
            *(unsigned int *)(curThing + 0x160) & ~0x80u;
    }
    if ((unsigned char)y == 0)
        return;
    snd = ((*(unsigned int *)(curThing + 0x160) & 0x80) != 0)
        ? (OnTheGround() ? &pmapCalled[0x1970] : &pmapCalled[0x1964])
        : &pmapCalled[0x1958];
    SoundOn(snd, 0x17, 0xaa, 0, curId, 0x9c4, 0x32, 0,
            0x50, 0, 0, 0, 0, 0, (short)-1);
}