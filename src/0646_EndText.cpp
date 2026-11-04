/* w38F_7df10_v1: ?EndText@@YGXXZ — shell-alloc bracket; buttonBoxes tail
 * release loop; rep-stos clear; fake extern for menuSelecting+8 field read. */
extern "C" void __stdcall PushShellAlloc(void);
extern "C" void __stdcall FreeTextStuff(void);
extern "C" void __stdcall PopShellAlloc(void);
extern "C" void __fastcall MMFreeHandle(long);
extern "C" long textNum;
extern "C" long buttonBoxes[64];
extern "C" void *__cdecl memset(void *, int, unsigned long);
extern long w38f_ms8;

void __stdcall EndText(void)
{
    long *p;
    PushShellAlloc();
    if (textNum == -1)
        goto clear;
    FreeTextStuff();
    if (textNum != -1)
        goto pop;
clear:
    for (p = &buttonBoxes[50]; p < &buttonBoxes[64]; p++)
        if (*p != 0 && *p != *(long *)&w38f_ms8)
            MMFreeHandle(*p);
    memset(&buttonBoxes[50], 0, 0x38);
pop:
    PopShellAlloc();
}