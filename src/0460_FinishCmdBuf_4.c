// @FinishCmdBuf@4 @ rva 0x62ea0 — with an unsigned short fastcall param CL
//   keeps the value in si (66 8b f1, probe d71); an int param spills 32-bit.
extern unsigned short cmdBufPos;
extern void __stdcall WriteCmdBufEnd(void);
extern void ReadCmdBuf(void);

void __fastcall FinishCmdBuf_q(unsigned short a)
{
    WriteCmdBufEnd();
    cmdBufPos = a;
    ReadCmdBuf();
}
