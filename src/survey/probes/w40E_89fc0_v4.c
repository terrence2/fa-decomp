/* rva 565184 (0x89fc0) v4 — v3 + volatile smpx/smpy so CL emits one
 * `32 c0 c2 10 00` block reached by the four jccs (v1 inlined it
 * 4x, v2's ||-merge pushed r into a pushed esi and shifted all arg
 * offsets); char return type because FA returns via al
 * (b0 01 / 32 c0). */
extern volatile short w40E_smpx;   /* = _shellMousePos (x word) */
extern volatile short w40E_smpy;   /* = _shellMousePos+0x2 */
extern short w40E_mpw;    /* = ?mousePtrWidth@@3FA */
extern short w40E_mph;    /* = ?mousePtrHeight@@3FA */
extern void w40E_ShellHideMouse(void);

char __stdcall w40E_CheckMousePtr(long a, long b, long c, long d)
{
    if ((short)c < w40E_smpx) goto ret0;
    if ((short)w40E_mpw + (short)w40E_smpx - 1 < (short)a) goto ret0;
    if ((short)d < w40E_smpy) goto ret0;
    if ((short)w40E_mph + (short)w40E_smpy - 1 < (short)b) goto ret0;
    w40E_ShellHideMouse();
    return 1;
ret0:
    return 0;
}