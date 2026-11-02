// w26a_8b760 @ rva 0x8b760 (571232, unnamed 16 B orphan) — FA bytes (raw;
// dis.py elides the 9 hidden lead bytes here):
//   66 c7 05 50 aa 4f 00 ff ff   mov word ptr ds:0x4faa50, 0xffff
//                                (?wingSay@@3PAUSAY@@A + 0x88)
//   c3                           ret
//   8d 9b 00 00 00 00            (6 B census pad)
// Direct imm16 store into the SAY struct field at wingSay+0x88. The
// +0x88 addend is baked by the extern-array spelling (FPSInit recipe).
extern char wingSay_t[];
void w26a_8b760(void)
{
    *(unsigned short *)(wingSay_t + 0x88) = 0xffffu;
}