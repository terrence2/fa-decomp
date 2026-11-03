// chunk @ rva 0xc890 (48 B = 37 code + 11 census pad lea esp fill) --
// unnamed void cdecl cleanup: ShellHideMouse(); stub call $FA$_t_40cc80;
// ShellShowMouse(); MMFreeHandle(invertItemBrush) (fastcall, ecx);
// invertItemBrush = 0; ret.  Plain C route.
// NOTE: replacing this chunk removes its stub anchor $FA$_t_40c890 ->
// alias 0=$FA$_t_40c890 (parent to check for anchor consumers).
extern void __stdcall ShellHideMouse(void);
extern void __stdcall ShellShowMouse(void);
extern void __fastcall MMFreeHandle(void*);   /* @MMFreeHandle@4 */
extern void* invertItemBrushq;                /* ?invertItemBrush@@3PAUT_HANDLE@@A */
extern void w34h_cc80(void);                  /* $FA$_t_40cc80 */

void w34h_c890(void)
{
    ShellHideMouse();
    w34h_cc80();
    ShellShowMouse();
    MMFreeHandle(invertItemBrushq);
    invertItemBrushq = 0;
}