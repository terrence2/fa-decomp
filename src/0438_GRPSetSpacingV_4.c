// @GRPSetSpacingV@4 @ rva 0x5ef10 (64 B) — FA asm (fastcall, FPO frame):
//   66 89 0d <_curThing+0xff> (mov word [curThing+0xff],cx — WORD store at
//   +0xff, sibling of SpacingH's +0xfd)/66 a1 <_curId>/6a 00/6a 00/50/
//   e8 _GRPPart@12/3c 01/75 ../ MSGSend arg pushes with tag 8 and size 2,
//   ptr = _curThing+0xff, id = 0x8001.  Sets the current group's vertical
//   spacing word and broadcasts it via
//   MSGSend(curId,0x8001,0,0,0x8000,8,&spacing,2) when GRPPart(curId,0,0)==1.
//   GRPSetType/SpacingH triplet twin; plain C exact (probe
//   build/w4probe/b20b_grpvs_v1.obj — exact).
extern char curThing[];
extern unsigned short curId;

extern char __stdcall GRPPart(short a, int b, int c);
extern void __stdcall MSGSend(short id, int a, int b, int c, int d, int e,
                              void *ptr, int f);

void __fastcall GRPSetSpacingV(short vv)
{
    *(short *)(curThing + 0xff) = vv;
    if (GRPPart(curId, 0, 0) == 1)
        MSGSend(curId, 0x8001, 0, 0, 0x8000, 8, curThing + 0xff, 2);
}