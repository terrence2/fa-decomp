// @TakeoffSpeed@0 @ rva 0x9b1d0 — mov ecx,1 / call @GetFlightEnvelope@4 /
//   xor ecx,ecx / mov cx,[eax+8] / mov eax,ecx / ret: unsigned short load
//   of env[+8] after GetFlightEnvelope(1). Probe d7b_tos2 exact modulo the
//   rel32 call target.
extern int __fastcall GetFlightEnvelope(int a);

int TakeoffSpeed_q(void)
{
    int e = GetFlightEnvelope(1);
    unsigned short r = *(unsigned short *)((char *)e + 8);
    return r;
}
