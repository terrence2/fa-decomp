// @HUDSetDisrupt@4 @ rva 0xa8f0 (64 B) — flash the radar-disrupt warning.
// FA: mov al,[lastWC+0x20]; test/jne exit; byte[lastWC+0x20]=1 (c6 05,
// dis.py-elided); eax=_currentTicks+0x200 -> [lastWC+0x44] (a1/a3);
// call _CPResetRWR@0; push 0/0ff/0ff/&str; call ?SingleSound@@YGFPADFEF@Z;
// ret (arg pushed last: the string, pushed via 68 imm form).
extern unsigned char lastWasInQC20;   /* ?lastWasInQuickCreator@@3DA+0x20 */
extern unsigned long lastWasInQC44;   /* ?lastWasInQuickCreator@@3DA+0x44 */
extern unsigned long currentTicks;
extern char disruptStr[];             /* ?hudslewLimitHdg@@3UWORD_POINT@@A+0x428 */
extern int __stdcall CPResetRWRQ(void);
extern short __stdcall SingleSoundS(char *name, short f1, unsigned char f2,
                                    short f3);

void __fastcall HUDSetDisrupt_q(unsigned char f)
{
    if (lastWasInQC20)
        return;
    lastWasInQC20 = 1;
    lastWasInQC44 = currentTicks + 0x200;
    CPResetRWRQ();
    SingleSoundS(disruptStr, 0xff, 0xff, 0);
}
