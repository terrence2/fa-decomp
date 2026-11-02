/* _CTDo_wm_break @ 0x657a0 (80B)
   FA: sub esp,4; call CTDoA (ax -> [esp]); call CTDoB (ax -> [esp+2]);
   svcNoMsg==0 -> MSGSend(word[_curId] in ecx, 0x8001, 0, 0, 0x8000, 5, buf, 4)
   (mov cx,[curId] scheduled between the arg8 push and the arg7 push).
   The fastcall param is UNUSED (never spilled). */
extern unsigned short CTDoA_q(void);        /* -> $FA$_t_464f60 */
extern unsigned short CTDoB_q(void);        /* -> $FA$_t_464e50 */
extern unsigned char svcNoMsg;              /* _serviceTicks+0xec */
extern unsigned short curId;                /* identity _curId */
extern void __stdcall MSGSend(unsigned short a, unsigned long b, unsigned long c,
                              unsigned long d, unsigned long e, unsigned long f,
                              unsigned short *g, int h);

void __fastcall CTDo_wm_break_q(unsigned long a)
{
    unsigned short buf[2];
    buf[0] = CTDoA_q();
    buf[1] = CTDoB_q();
    if (svcNoMsg == 0)
        MSGSend(curId, 0x8001, 0, 0, 0x8000, 5, buf, 4);
}
