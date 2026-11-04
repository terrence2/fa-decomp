/* v3 = v2 + one band patch (0x1c: CL '05 imm32'/'pop'/'ret' -> FA's
 * 'pop; nop; lea eax,[eax*1+moffs]' with newsite DIR32 at site 5,
 * payload zeros, map addend +0x28). */
extern void __fastcall w33h_svcerr(int code);   /* $FA$_t_4659e0 */
extern char svcTb[];                            /* -> _serviceTicks+0x28 */

int __fastcall w33h_662a0(short s)
{
    short t = s;
    if (t < 0 || t > 4)
        w33h_svcerr(3);
    return (int)(svcTb + t);
}
