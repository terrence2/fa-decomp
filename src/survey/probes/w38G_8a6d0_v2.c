/* w38G (unnamed) @ 0x8a6d0 (48 B, stdcall ret 0xc) — v2: non-static.
 * FA: push esi/edi; w and p loaded 16-bit (66 8b) into di/esi; signed
 * jle wrapper around ShellHideMouse + tail call + ShellShowMouse. */
extern void __stdcall ShellHideMouse(void);          /* -> ?ShellHideMouse@@YGXXZ */
extern void __stdcall ShellShowMouse(void);          /* -> ?ShellShowMouse@@YGXXZ */
extern void __stdcall w38g_x48a700(void *, short, short);  /* -> $FA$_t_48a700 */

void __stdcall w38g_sm86(void *p, short w, short a3)
{
    if (*(short *)((char *)p + 0xa) > w) {
        ShellHideMouse();
        w38g_x48a700(p, w, a3);
        ShellShowMouse();
    }
}