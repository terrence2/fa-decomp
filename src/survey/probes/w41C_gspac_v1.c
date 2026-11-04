// w41C candidate 0x5e1a0 (0x45E1A0, 64 B) — twin of @GRPSetSpacingH@4
// (rva 0x5eed0, converted EXACT) with _WNGPart@12 swapped for _GRPPart@12.
//   66 a1 <_curId> / 6a 00 / 66 89 0d <_curThing+0xfd> (mov word, hidden
//   from dis.py) / 6a 00 / 50 / e8 _WNGPart@12 / 3c 01 / 75 23 / MSGSend
//   pushes 2/&curThing+0xfd/7/0x8000/0/0/0x8001/eax / c3 / 90 tail.
extern char curThing[];
extern unsigned short curId;

extern char __stdcall WNGPart(short a, int b, int c);
extern void __stdcall MSGSend(short id, int a, int b, int c, int d, int e,
                              void *ptr, int f);

void __fastcall w41C_wngSpacing(short hv)
{
    *(short *)(curThing + 0xfd) = hv;
    if (WNGPart(curId, 0, 0) == 1)
        MSGSend(curId, 0x8001, 0, 0, 0x8000, 7, curThing + 0xfd, 2);
}