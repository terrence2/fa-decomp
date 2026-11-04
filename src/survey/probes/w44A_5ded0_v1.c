/* unnamed 0x5ded0: fastcall(cl=byte param). WNGPart(curId,0,0); if ret==2 &&
   param: WNGFormationMove(byte[+0xfc], word[+0xfd], word[+0xff]);
   return byte[+0xfb]; else return 0. bl flag latch. */
extern unsigned short w44aCurId;      /* map: _w44aCurId=_curId */
extern unsigned char w44aCTfb;        /* map: _w44aCTfb=_curThing+0xfb */
extern unsigned char w44aCTfc;        /* map: _w44aCTfc=_curThing+0xfc */
extern unsigned short w44aCTfd;       /* map: _w44aCTfd=_curThing+0xfd */
extern unsigned short w44aCTff;       /* map: _w44aCTff=_curThing+0xff */
extern unsigned char __stdcall WNGPart(long id, long a2, long a3);
extern void __stdcall WNGFormationMove(unsigned char a1, unsigned short a2,
                                       unsigned short a3);

unsigned char __fastcall w44ac5ded0(unsigned char p)
{
    unsigned short w = w44aCurId;
    if (WNGPart(w, 0, 0) == 2) {
        if (p) {
            WNGFormationMove(w44aCTfc, w44aCTfd, w44aCTff);
        }
        return w44aCTfb;
    }
    return 0;
}