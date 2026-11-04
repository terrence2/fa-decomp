/* w44C de300 — cdecl 3 args: base char*, long delta, unsigned char* slot.
 * FA: sar >>12 (signed), counter at __adbgmsg+0x1070 (0x51bd18), call
 * f4de1c0 at rel32 (-0x182) with push 0x10. */
extern long w44c_adbgmsg;
extern void __cdecl w44c_f4de1c0(long);

void w44c_de3f0(char *arg1, long arg2, unsigned char *arg3)
{
    long e;
    unsigned char d;

    e = arg2 - *(long *)(arg1 + 0x810);
    e >>= 12;
    arg1 += e;
    d = *arg3;
    *(unsigned char *)(arg1 + 0x10) += d;
    *arg3 = 0;
    *(unsigned char *)(arg1 + 0x810) = 0xf1;
    if (*(unsigned char *)(arg1 + 0x10) != 0xf0)
        return;
    ++w44c_adbgmsg;
    if (w44c_adbgmsg == 0x20)
        w44c_f4de1c0(0x10);
}