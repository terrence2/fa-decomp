/* w43F 0x7ddb0 (64 B, stdcall 4 args ret 0x10): arg1 -> @MMAccessR@4 (ecx
 * fastcall, identity); b = *(long*)(ret+0x2a) (dword read); arg2 byte loaded
 * via mov cl,[esp+8] with xor ecx,ecx zero-extend; c = b + (n*3)*2 via the
 * lea pair [ecx+ecx*2] / [edx+ecx*2]; arg3/arg4 pointer stores of the short
 * reads *(short*)(c+2) / *(short*)(c+4) (movsx), each guarded by test/je;
 * return *(short*)(c+2) re-read.  Tail 05 00 00 00 00 (census).
 */
extern long __fastcall MMAccessR(long a);

long __stdcall w43F_7ddb0(long id, unsigned char n, long *p3, long *p4)
{
    unsigned long b, c;
    b = *(unsigned long *)((char *)MMAccessR(id) + 0x2a);
    c = (unsigned long)n * 3;
    c = b + c * 2;
    if (p3 != (long *)0) *p3 = (long)*(short *)(c + 2);
    if (p4 != (long *)0) *p4 = (long)*(short *)(c + 4);
    return (long)*(short *)(c + 2);
}