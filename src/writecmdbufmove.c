// @WriteCmdBufMove@4 @ rva 0x62e80 (16 B)
// FA: push 0x20 / mov edx,ecx / xor ecx,ecx / call @WriteCmdBuf@12 / ret
extern long __fastcall WriteCmdBuf(int, int, int);

long __fastcall WriteCmdBufMove(int a)
{
    return WriteCmdBuf(0, a, 0x20);
}
