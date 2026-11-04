// _T_InitDictionary@0 @ rva 0xa7480 (96 B; FPO locals 4; code 92 B +
// 3-B 8d 49 00 tail).  stdcall void.  Loop over tdic entries (53-B stride):
// push n / tdicSize = n / sprintf(buf@+4, fmt@0x4ec968
// (=?mcFlyAll@@3DA+0x46c), tmapName, n) / fastcall
// @T_InitDictionaryEntry@8(&buf, [tdicSize]) (uchar ret); if zero, exit; else
// m = [tdicSize] (fresh load), k = m+1, tdicSize = k, the dis.py-ELIDED
// byte store `mov [tdic-1 + k + 4*(3m)],bl` = w43H_tdicM1[k-1+12m] = 0,
// cmp k,0x12c / jl loop.
extern char w43H_tdicM1[];   /* =_PLthrustYaw+0x7 (i.e. tdic-1) */
extern long w43H_tdicSize[]; /* =_tdicSize */
extern char w43H_tmapName[]; /* =_tmapName */
extern char w43H_fmt[];      /* =?mcFlyAll@@3DA+0x46c */
extern long __cdecl w43H_sprint(char *buf, const char *fmt, ...); /* =_w43H_sprint=_Sprintf */
extern unsigned char __fastcall w43H_tide(char *buf, long n); /* =@w43H_tide@8=@T_InitDictionaryEntry@8 */

void __stdcall w43H_TInitDictionary2(void)
{
    unsigned long blk[4];
    long n = 0;
    long m, k;
    for (;;) {
        w43H_tdicSize[0] = n;
        w43H_sprint((char *)&blk[1], w43H_fmt, w43H_tmapName, n);
        if (!w43H_tide((char *)&blk[1], w43H_tdicSize[0]))
            break;
        m = w43H_tdicSize[0];
        k = m + 1;
        w43H_tdicSize[0] = k;
        w43H_tdicM1[k - 1 + 4 * (m + m + m)] = 0;
        if (k >= 0x12c)
            break;
        n = k;
    }
}