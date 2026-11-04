/* w35G @SetThrottle@4 @ rva 0x51120 (96 B) v1
 * FA 88 B code + 8 B tail (8d642400 x2), fastcall(long n) [arg low word used]:
 *   push esi / a1 [fl] / mov esi,ecx / test al,0x10 / jne L1
 *   / 66 89 35 [w2],si (mov WORD [0x50892a],si)
 *   L1: call _LimitThrottle@0
 *   / cmp esi,0x64 / jle L2
 *   / a1 [tt] / test eax,eax / je L2
 *   / a1 [fl] / test al,8 / jne L2
 *   / or eax,0x20 / pop esi / a3 [fl]
 *   / 66 a1 [ct] / 66 05 18 00 / 66 a3 [tq] / c3
 *   L2: a1 [fl] / pop esi / 83 e0 df / a3 [fl] / c3
 */
extern unsigned long w35g_fl;        /* =_curThing+0x16f */
extern unsigned short w35g_th;       /* =_curThing+0x1f2 */
extern unsigned long w35g_tt;        /* =_curThingType+0x153 */
extern unsigned short w35g_ct;       /* =_currentT */
extern unsigned short w35g_tq;       /* =_curThing+0x274 */
extern void __stdcall w35g_ltm(void);    /* =_LimitThrottle@0 */

void __fastcall SetThrottle_q(long n)
{
    unsigned long flags = w35g_fl;
    if (!(flags & 0x10))
        w35g_th = (unsigned short)n;
    w35g_ltm();
    if (n > 100) {
        if (w35g_tt != 0) {
            flags = w35g_fl;
            if (!(flags & 0x08)) {
                w35g_fl = flags | 0x20;
                w35g_tq = w35g_ct + 0x18;
                return;
            }
        }
    }
    w35g_fl &= ~0x20;
}