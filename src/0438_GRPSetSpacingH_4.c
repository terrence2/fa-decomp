// @GRPSetSpacingH@4 @ rva 0x5eed0 (64 B) — FA asm (fastcall, FPO frame):
//   66 89 0d <_curThing+0xfd> (mov word [curThing+0xfd],cx — WORD store,
//   hidden by dis.py's byte-granularity scan, decoded from raw)/
//   66 a1 <_curId>/6a 00/6a 00/50/e8 _GRPPart@12/3c 01/75 ../ MSGSend arg
//   pushes with tag 7 and size 2, ptr = _curThing+0xfd, id = 0x8001.
//   Sets the current group's horizontal spacing word and broadcasts it via
//   MSGSend(curId,0x8001,0,0,0x8000,7,&spacing,2) when GRPPart(curId,0,0)==1.
//   GRPSetType/V triplet twin; plain C exact (probe
//   build/w4probe/b20b_grpsh_v1.obj — exact).
extern char curThing[];
extern unsigned short curId;

extern char __stdcall GRPPart(short a, int b, int c);
extern void __stdcall MSGSend(short id, int a, int b, int c, int d, int e,
                              void *ptr, int f);

void __fastcall GRPSetSpacingH(short hv)
{
    *(short *)(curThing + 0xfd) = hv;
    if (GRPPart(curId, 0, 0) == 1)
        MSGSend(curId, 0x8001, 0, 0, 0x8000, 7, curThing + 0xfd, 2);
}