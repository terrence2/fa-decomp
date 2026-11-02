/* $FA$_t_49d830 @ rva 0x9d830 (dec 645168), 32 B. FA bytes:
 *   a0 1b 88 50 00   mov al,ds:_curThing+0xe3
 *   3c 13            cmp al,0x13 ; 72 0e  jb +14 (out)
 *   3c 1e            cmp al,0x1e ; 77 0a  ja +10
 *   b9 1f 00 00 00   mov ecx,0x1f
 *   e9 79 5c fc ff   jmp @EnterState@4     (fastcall state dispatcher)
 *   c3               ret
 * void fastcall@0: plain ret; tail-call EnterState(0x1f) when the
 * _curThing+0xe3 kind byte is in [0x13,0x1e].
 */
extern unsigned char curThing[0x4000];   /* =_curThing */
extern void __fastcall EnterState(int st);   /* =@EnterState@4 */

void __fastcall w30a_9d830(void)
{
    unsigned char c = curThing[0xe3];
    if (c >= 0x13 && c <= 0x1e) EnterState(0x1f);
}