// 0x10450 = 66608, unnamed gap, 16 B (14 code + 8bff pad)
// FA asm (fastcall — _DAMAGEDoHit@12 calls it 11x with operands in ecx/edx):
//   lea eax,[edx+ecx*1] / cmp eax,0x64 / jle ret / mov eax,0x64 / ret.
// Sum of the two fastcall args clamped to <= 100.
int __fastcall w25c_min100_q(int a, int b)
{
    int s;
    s = a + b;
    if (s > 100)
        s = 100;
    return s;
}