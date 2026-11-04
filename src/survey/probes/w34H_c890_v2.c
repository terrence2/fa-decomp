// chunk @ rva 0xc890 (48 B = 37 code + 11 census pad lea esp fill) --
// unnamed void cdecl cleanup: ShellHideMouse(); stub call $FA$_t_40cc80;
// ShellShowMouse(); MMFreeHandle(invertItemBrush) (fastcall, ecx);
// invertItemBrush = 0; ret.  Plain C route (v1 EXACT).  v2: Shell* are
// C++-mangled publics -> map the CL-emitted stdcall names (@0 spellings)
// onto ?Shell*Mouse@@YGXXZ.
// NOTE: replacing this chunk removes its stub anchor $FA$_t_40c890 ->
// alias 0=$FA$_t_40c890 (parent to check for anchor consumers).
extern void __stdcall w34h_smHide(void);   /* ?ShellHideMouse@@YGXXZ */
extern void __stdcall w34h_smShow(void);   /* ?ShellShowMouse@@YGXXZ */
extern void __fastcall MMFreeHandle(void*);   /* @MMFreeHandle@4 */
extern void* invertItemBrushq;             /* ?invertItemBrush@@3PAUT_HANDLE@@A */
extern void w34h_cc80(void);               /* $FA$_t_40cc80 */

void w34h_c890(void)
{
    w34h_smHide();
    w34h_cc80();
    w34h_smShow();
    MMFreeHandle(invertItemBrushq);
    invertItemBrushq = 0;
}