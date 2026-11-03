/* rva 0x662a0 (48 B): short s in cx: if (s < 0 || s > 4) svcerr(3);
 * return table_base_0x5423f0 + (int)s (movsx eax,si; lea eax,
 * [eax*1 + 0x5423f0]; that lea is live code sitting in the "tail"
 * band: 8d 04 85 <VA> before c3).  svcerr = $FA$_t_4659e0 (ecx=3). */
extern void w33h_svcerr(int code);      /* $FA$_t_4659e0, fastcall */
extern char svcTb[];                    /* -> _serviceTicks+0x28 */

int __fastcall w33h_662a0(short s)
{
    short t = s;
    if (t < 0 || t > 4)
        w33h_svcerr(3);
    return (int)(svcTb + t);
}
