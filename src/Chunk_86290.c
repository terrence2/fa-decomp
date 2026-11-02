// 0x86290 (16 B) — call ?PushShellAlloc@@YGXXZ; jmp ?ShellHideMouse@@YGXXZ;
// pad (8d9b0000 0000). Void 0-arg wrapper whose 2nd call is tail-jmp'd.
extern void __stdcall PushShellAlloc_f(void);
extern void __stdcall ShellHideMouse_f(void);
void __fastcall w27a_sph_q(void)
{
    PushShellAlloc_f();
    ShellHideMouse_f();
}