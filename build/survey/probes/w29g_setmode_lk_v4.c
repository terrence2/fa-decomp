/* w29g __setmode_lk @ 0xe4690 — v4: int ftext (FA zero-extends into edx via
 * xor edx,edx + mov dl,al dance) */
extern char w29g_pio[];              /* -> __crtheap+0x4 */
extern int *__cdecl w29g_errno(void);   /* -> __errno */

int __cdecl w29g_smlk(int fh, int mode)
{
    unsigned char *p;
    unsigned char osfile;
    int ftext;
    p = (unsigned char *)*(unsigned long *)((char *)w29g_pio + ((fh & ~0x18) >> 3)) + (((fh & 0x1f) << 2) * 9) + 4;
    osfile = *p;
    ftext = osfile & 0x80;
    if (mode == 0x8000)
        osfile &= ~0x80;
    else if (mode == 0x4000)
        osfile |= 0x80;
    else {
        *w29g_errno() = 0x16;
        return -1;
    }
    *p = osfile;
    return ftext ? 0x4000 : 0x8000;
}