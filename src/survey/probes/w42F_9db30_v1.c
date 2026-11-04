/* _PLANEProc @ rva 0x9db30 (96 B) -- w42F v1. Same dispatcher family as the
 * converted GVProc (_GVProc 0x72d00, w16b_2 exact): uchar param loaded
 * `xor ecx,ecx / mov al,[esp+4] / mov cl,al`, 8-case switch (ff 24 8d inline
 * .text jump table at +0x3c, HARDStoreWeight recipe), case arms return the
 * FA handler addresses (b8 <imm> dirs), default/cases 1/4/5 shared-tail into
 * a cdecl push eax / call _GVProc / add esp,4 forward. */
extern long PLANEAddProc(void);
extern long PLANEMoveProc(char p);
extern long PLANEEventProc(void);
extern long PLANESayProc(void);
extern long PLANECommentProc(void);
extern long GVProc(unsigned char c);

long PLANEProc(unsigned char c)
{
    switch (c) {
    case 0:
        return (long)PLANEAddProc;
    case 2:
        return (long)PLANEMoveProc;
    case 3:
        return (long)PLANEEventProc;
    case 6:
        return (long)PLANESayProc;
    case 7:
        return (long)PLANECommentProc;
    }
    return (long)GVProc(c);
}