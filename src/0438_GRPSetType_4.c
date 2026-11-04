// @GRPSetType@4 @ rva 0x5ee90 (64 B) — FA asm (fastcall, FPO frame):
//   88 0d <_curThing+0xfc> (mov byte [curThing+0xfc],cl — the type store is
//   byte-wide, emitted INTERLEAVED between the MSGSend push imm32s)/
//   66 a1 <_curId> (mov ax,[curId])/6a 00/6a 00/50 (push eax=curId)/
//   e8 _GRPPart@12 / 3c 01 (cmp al,1)/75 .. (jne exit)/ MSGSend arg pushes:
//   6a 09 6a 01 68 <_curThing+0xfc> 68 8000 6a 00 6a 00 68 8001 66 <curId>
//   push — then e8 _MSGSend@32.  Sets the current group's type byte and
//   broadcasts it via MSGSend(curId,0x8001,0,0,0x8000,9,&type,1) when
//   GRPPart(curId,0,0)==1.  GRPSetSpacingH/V triplet twin; plain C exact —
//   FA/CL both sink the store between the arg pushes (probe
//   build/w4probe/b20b_grp_v1.obj — exact).
extern char curThing[];
extern unsigned short curId;

extern char __stdcall GRPPart(short a, int b, int c);
extern void __stdcall MSGSend(short id, int a, int b, int c, int d, int e,
                              void *ptr, int f);

void __fastcall GRPSetType(char type)
{
    *(char *)(curThing + 0xfc) = type;
    if (GRPPart(curId, 0, 0) == 1)
        MSGSend(curId, 0x8001, 0, 0, 0x8000, 9, curThing + 0xfc, 1);
}