/* w30f mouse thunk @ rva 0x881b0 (dec 557488), 32 B (20 B code + 12 B pad)
 * FA:
 *   e8 rel32      call ?ShellShowMouse@@YGXXZ
 *   b9 01 00 00 00 mov ecx,1
 *   e8 rel32      call @G_Flush@4
 *   e9 rel32      jmp ?ShellHideMouse@@YGXXZ   (void tail call)
 */
void __stdcall ShellShowMouse(void);
void __fastcall G_Flush(int f);
void __stdcall ShellHideMouse(void);

void w30f_mou_v1(void)
{
    ShellShowMouse();
    G_Flush(1);
    ShellHideMouse();
}