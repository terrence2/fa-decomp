/* w35G @GRPSetControl@8 @ rva 0x5ee20 (112 B) v1 — fastcall(uchar c, char d)
 * FA 91 B code + 5 B tail (05 00 00 00 00):
 *   sub esp,4 / test dl,dl / mov [esp+3],cl (s=c store after test) / jge L1
 *   d<0: a0 [g0] / 3a c8 (cmp cl,al — live c param) / jae exit
 *   L1(after test dl,dl 2nd): jle L2            (d>0 test at 0x45ee34/7e 0d)
 *   d>0: a0 [g0] / 8a 4c 24 03 (s reload) / 3a c8 (cmp cl,al) / jbe exit
 *   L2: 66 8b 0d [curId],cx (mov cx, WORD _curId!) / 8a 44 24 03 (s)
 *       / push 0 (arg3) / a2 [g0] (g0 = s) / push 0 (arg2) / push ecx (arg1)
 *       / call _GRPPart@12 (stdcall) / 3c 01 (cmp al,1) / jne exit
 *   push 1 / 66 8b 0d [curId],cx / push eax (&s after lea) / push 0xa
 *       / push 0x8000 / push 0 / push 0 / push 0x8001 / push ecx / call MSGSend
 *   exit: add esp,4 / c3
 */
extern unsigned char w35g_gv;      /* =_curThing+0xfb */
extern volatile unsigned short w35g_ci;    /* =_curId */
extern char __stdcall w35g_gp(long, long, long);   /* =_GRPPart@12 */
extern void __stdcall w35g_ms(long id, long f1, long z1, long z2,
                              long f2, long cmd, void *s, long on); /* =_MSGSend@32 */

void __fastcall GRPSetControl_q(unsigned char c, signed char d)
{
    unsigned char s;
    s = (unsigned char)c;
    if (d < 0) {
        if (c >= w35g_gv)
            return;
    } else if (d > 0) {
        if (s <= w35g_gv)
            return;
    }
    w35g_gv = s;
    if (w35g_gp(w35g_ci, 0, 0) == 1)
        w35g_ms(w35g_ci, 0x8001, 0, 0, 0x8000, 10, &s, 1);
}