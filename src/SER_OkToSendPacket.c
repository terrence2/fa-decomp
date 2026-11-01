// ?SER_OkToSendPacket@@YADXZ @ rva 0xa90d0 (32 B) — FA asm: c6 05 <Ctrl+0x344>,
//   1 (flag store first)/83 3d <Ctrl+0x22>,0x18/0f 93 c0 (setae al — unsigned
//   >=)/c3.  Plain C exact: byte store as c6 05, dword cmp against imm8 as
//   83 3d, unsigned long extern keeps the setae polarity, char return leaves
//   al unzeroed.  Probe build/w4probe/w19_oktosend_v1.obj — exact.
extern unsigned char serOkFlag;    /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x344 */
extern unsigned long serQDepth;    /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x22 */

char SER_OkTP_f(void)
{
    serOkFlag = 1;
    return (char)(serQDepth >= 0x18);
}