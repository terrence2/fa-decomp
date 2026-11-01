// @WriteCmdBufEnd@0 @ rva 0x62e90 (16 B)
// FA: push 0 / xor edx,edx / mov ecx,2 / call @WriteCmdBuf@12 / ret
extern long __fastcall WriteCmdBuf(int, int, int);

long __fastcall WriteCmdBufEnd(void)
{
    return WriteCmdBuf(2, 0, 0);
}
