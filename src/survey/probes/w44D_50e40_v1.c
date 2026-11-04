/*
 * w44D_50e40_v1.c — @FMCopyAngles@4 @ 0x450e40 (128 B, fpo/esp)
 * Fastcall(WORD copy in cx).  Bidirectional angle copy between curThing
 * float(24.8) fields (+0x197/+0x193/+0x18f) and pixel-angle WORDs
 * (+0x1d/+0x1f/+0x21) through PAToF24/F24ToPA; third slot negated
 * (16-bit neg cx for PAToF24 arg, 32-bit neg ecx for F24ToPA arg).
 * FA "lags" stores one slot behind the next arg load.
 */
extern char curThing[];
extern int __fastcall PAToF24(unsigned short a);
extern unsigned short __fastcall F24ToPA(int f);

void __fastcall FMCopyAngles(unsigned long copy)
{
    if ((unsigned char)copy != 0) {
        *(int *)(curThing + 0x197) = PAToF24(*(unsigned short *)(curThing + 0x1d));
        *(int *)(curThing + 0x193) = PAToF24(*(unsigned short *)(curThing + 0x1f));
        *(int *)(curThing + 0x18f) =
            PAToF24((unsigned short)(-(short)(*(unsigned short *)(curThing + 0x21))));
    } else {
        *(unsigned short *)(curThing + 0x1d) = F24ToPA(*(int *)(curThing + 0x197));
        *(unsigned short *)(curThing + 0x1f) = F24ToPA(*(int *)(curThing + 0x193));
        *(unsigned short *)(curThing + 0x21) = F24ToPA(-*(int *)(curThing + 0x18f));
    }
}