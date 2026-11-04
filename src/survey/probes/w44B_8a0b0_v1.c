/* unnamed @ rva 0x8a0b0 (dec 565424), size 0x50:
 * fastcall gate f1(cursorLastTicks, cursorTicks) -> al bool;
 * if false return; if (cursorOn) f2() else f3();
 * cursorLastTicks = TIMESystemTime(); cursorTicks = TIMESystemTime()+3.
 * All four calls are BAKED rel32 in FA (no .reloc entries).
 */
extern unsigned long cursorTicks;
extern unsigned long cursorLastTicks;
extern unsigned char cursorOn;
extern char __fastcall w44B_f1(unsigned long, unsigned long);
extern void w44B_f2(void);
extern void w44B_f3(void);
extern unsigned long __stdcall TIMESystemTime(void);

void w44B_tick(void)
{
    if (w44B_f1(cursorLastTicks, cursorTicks) == 0)
        return;
    if (cursorOn != 0)
        w44B_f2();
    else
        w44B_f3();
    cursorLastTicks = TIMESystemTime();
    cursorTicks = TIMESystemTime() + 3;
}