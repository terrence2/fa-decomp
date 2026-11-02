// 0x862a0 (16 B) — call ?PopShellAlloc@@YGXXZ; jmp ?ShellShowMouse@@YGXXZ;
// pad. Same recipe as sph.
extern void __stdcall PopShellAlloc_f(void);
extern void __stdcall ShellShowMouse_f(void);
void __fastcall w27a_sps_q(void)
{
    PopShellAlloc_f();
    ShellShowMouse_f();
}