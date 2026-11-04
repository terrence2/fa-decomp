/* rva 0x20610 (80 B) - fort ground forces text panel
 * FA: push 0; eax=[curDialog]; movsx [eax+0xa]+0xb (arg6 y); push 5; push 0x20;
 * push 0x108; push eax; eax=[curDialog] RELOAD; movsx [eax+8]+0x17 (arg5 x);
 * push eax; push 2/0/0; push 0x4ec100 (fortnationgroundforces+0x1130 arg1);
 * call PrepareText (stdcall 10 args); xor ecx,ecx; call PrintText(0) fastcall;
 * jmp FreeTextStuff (tail).
 * RIGHT-TO-LEFT: arg10=0 pushed first.
 */
extern char *curDialogP;
extern char w43aFortS[];
extern long __stdcall w43aPrep(char *, long, long, long, long, long, long, long, long, char);
extern void __fastcall w43aPrint(long);
extern void __stdcall w43aFreeText(void);

void w43A_20610(void)
{
    w43aPrep(w43aFortS,
             0, 0, 2,
             (long)*(short *)&curDialogP[8] + 0x17,
             (long)*(short *)&curDialogP[0xa] + 0xb,
             0x108, 0x20, 5, 0);
    w43aPrint(0);
    w43aFreeText();
}