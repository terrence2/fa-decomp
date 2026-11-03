/* wave 31C: @FMHook@4 (FA rva 0x51250, 0x60 B) v1 */
extern char w31cScls[];        /* _pmapCalled+0x1934 = "&FLAPCLS.5K" */
extern char w31cSopn[];        /* _pmapCalled+0x1928 = "&FLAPOPN.5K" */
extern unsigned long w31cFlg;  /* _curThingType+0xba */
extern unsigned short w31cCid; /* _curId */
extern unsigned long w31cCt;   /* _curThing+0x16f */
extern char __stdcall w31cSon(char *, short, short, char, unsigned short, short,
                              short, char, short, short, unsigned short,
                              unsigned short, short, unsigned char, short);

void __fastcall w31cFM(unsigned char c)
{
    if ((w31cFlg & 2) == 0) return;
    if (c == 0) {
        w31cSon(w31cSopn, 0x17, 0x4b, 0, w31cCid, 0x9c4, 0x32, 0, 0x50, 0,
                0, 0, 0, 0, -1);
        w31cCt &= 0xfffffbff;
    } else {
        w31cSon(w31cScls, 0x17, 0x4b, 0, w31cCid, 0x9c4, 0x32, 0, 0x50, 0,
                0, 0, 0, 0, -1);
        w31cCt |= 0x400;
    }
}