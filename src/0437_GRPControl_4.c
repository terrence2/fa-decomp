// @GRPControl@4 @ rva 0x5ec00 = 388096, 80 B (fastcall 1 byte arg -> ecx;
// FA: mov ax,[_curId] (word); push ebx; mov bl,cl; push 0; push 0; push eax;
// call _GRPPart@12; cmp al,2; jne Lz; test bl,bl; je Lr; [word +0xff / byte
// +0xfc / word +0xfd loads]; push eax; push ecx; push edx; call
// _GRPFormationMove@12; Lr [byte +0xfb]; pop ebx; ret // Lz: xor al,al).
extern unsigned short w26_curId; /* map _w26_curId=_curId */
extern unsigned char w26_ctBfb; /* map _w26_ctBfb=_curThing+0xfb */
extern unsigned char w26_ctBfc; /* map _w26_ctBfc=_curThing+0xfc */
extern unsigned short w26_ctWfd; /* map _w26_ctWfd=_curThing+0xfd */
extern unsigned short w26_ctWff; /* map _w26_ctWff=_curThing+0xff */
extern unsigned char __stdcall GRPPartQ(unsigned short a, unsigned int b, unsigned int c); /* map _GRPPartQ@12=_GRPPart@12 */
extern unsigned char __stdcall GRPFormationMoveQ(unsigned char a, unsigned short b, unsigned short c); /* map _GRPFormationMoveQ@12=_GRPFormationMove@12 */

unsigned char __fastcall w26c_GRPControl_q(unsigned char p1)
{
    unsigned char r = (unsigned char)GRPPartQ(w26_curId, 0, 0);
    if (r == 2) {
        if (p1)
            GRPFormationMoveQ(w26_ctBfc, w26_ctWfd, w26_ctWff);
        return w26_ctBfb;
    }
    return 0;
}