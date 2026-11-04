/* FA 0x89a10 (62 B code + 8b ff pad): bitmap-pool pre-register, "better".
 * char buf[16]; int i;
 * SetupBitmapAccess(0, 0, 0);
 * for (i = 4; i >= 0; i--) { Sprintf(buf, checkRightButton + 0x2e4, i);
 *                             RMAccess(buf, 0x8004); }
 * FA shapes: 83 ec 10; push esi; 6a 00 6a 00 (two arg pushes), be 04 00 00 00
 * (esi init), 6a 00 (third push), call SetupBitmapAccess@12 (callee pops 12);
 * loop at +0x14: lea eax,[esp+4] (buf), push esi (arg3, i), push fmt imm32
 * (68 <VA> DIR32), push eax, call _Sprintf (cdecl, caller cleans 12);
 * lea eax,[esp+0x10]; add esp,0xc; push 0x8004; push eax; call RMAccess@8
 * (stdcall). Loop latch: 4e dec esi / 79 db jns (dec-then-test, 16 iters).
 * Siblings: 0x89440 (esi=6, fmt +0x284 "^GUYGOOD"), 0x89a10 (esi=4,
 * fmt +0x2e4 "better"), 0x89a50 (esi=4, fmt +0x2f4 "Evasive action").
 */
extern char checkRightButton[];
extern void __stdcall SetupBitmapAccess(int a, int b, int c);
extern int Sprintf(char *buf, char *fmt, ...);
extern int __stdcall RMAccess(char *name, int flags);

void w45E_89a10_v1(void)
{
    char buf[16];
    int i;

    SetupBitmapAccess(0, 0, 0);
    for (i = 4; i >= 0; i--) {
        Sprintf(buf, checkRightButton + 0x2e4, i);
        RMAccess(buf, 0x8004);
    }
}