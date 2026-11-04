/* wave-41A probe v1: unnamed chunk 0x40c8c0 (64 B) — shutdown: hide mouse,
 * call 0xcd20, show mouse, free invertSubItem, zero it. */
/* FA: (word)subMenuPress+2 = 0; hide(); mid(); show();
 *     if (curSubItem) { MMFreeHandle(invertSubItem); invertSubItem = 0; } */
extern char w41a_smp2[];          /* ?subMenuPress@@3UWORD_POINT@@A+0x2 = VA 0x51d67a */
extern void *w41a_csi;            /* ?curSubItem@@3PAUMENU_ITEM@@A = 0x4e81d8 */
extern void *w41a_isi;            /* ?invertSubItem@@3PAUT_HANDLE@@A = 0x4e81fc */

void __stdcall w41a_hide(void);   /* ?ShellHideMouse@@YGXXZ */
void __stdcall w41a_mid(void);    /* $FA$_t_40cd20 (still-stub chunk 0xcd20) */
void __stdcall w41a_show(void);   /* ?ShellShowMouse@@YGXXZ */
void __fastcall w41a_mmfh(void *);/* @MMFreeHandle@4 */

void __cdecl w41a_c8c0(void)
{
    *(unsigned short *)w41a_smp2 = 0;
    w41a_hide();
    w41a_mid();
    w41a_show();
    if (w41a_csi) {
        w41a_mmfh(w41a_isi);
        w41a_isi = 0;
    }
}