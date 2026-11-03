/* v2: svcerr is __fastcall (FA: mov ecx,3; call — no push/cleanup).
 * FA return: movsx eax,si; pop esi; nop; lea eax,[eax*1 + moffs 0x5423f0];
 * ret.  The movsx-then-pop order + sib-moffs lea will need one patch. */
extern void __fastcall w33h_svcerr(int code);   /* $FA$_t_4659e0 */
extern char svcTb[];                            /* -> _serviceTicks+0x28 */

int __fastcall w33h_662a0(short s)
{
    short t = s;
    if (t < 0 || t > 4)
        w33h_svcerr(3);
    return (int)(svcTb + t);
}
