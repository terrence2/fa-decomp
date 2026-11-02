// _MOUSEInit@0 @ rva 0x97e20 — return uchar so FA's b0 01 appears both paths.
extern unsigned char w27a_v60b;      /* _vHzMod+0x60 */
extern unsigned char w27a_mkB;       /* _mouseButtons */
extern unsigned short w27a_mcs18w;   /* mouse_critical_section+0x18 */
extern unsigned short w27a_press4c;  /* _mouseButtonPresses+0x4c */
extern char w27a_mcsB[];             /* mouse_critical_section base */
void __declspec(dllimport) __stdcall InitializeCriticalSectionQ(void *cs);
unsigned char __stdcall w27a_mi_q(void)
{
    unsigned short r;
    if (w27a_v60b == 1)
        return 1;
    r = 0;
    w27a_mcs18w = (unsigned short)r;
    w27a_mkB = (unsigned char)r;
    w27a_press4c = (unsigned short)r;
    InitializeCriticalSectionQ(&w27a_mcsB[0]);
    r = 1;
    w27a_mkB = 1;
    return (unsigned char)r;
}
