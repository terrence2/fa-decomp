// @BasicSound@8 @ rva 0x330f0 — 15 pushes (fastcall a1=ecx=s, a2=edx=x) and
//   tail-jmp into FA's 15-arg stdcall SoundOn (no caller esp cleanup — the
//   cdecl decl emitted 83 c4 3c, d100 v1) (probe d100 exact).
extern char __stdcall SoundOn(char *s, int a1, int a2, int a3, int a4, int a5,
                              int a6, int a7, int a8, int a9, int a10,
                              int a11, int a12, int a13, int a14);

void __fastcall BasicSound_q(char *s, int x)
{
    SoundOn(s, 1, 0xff, 0, 0, -1, -1, 0, 0, -1, 0xffff, 0xffff, x, 0, -1);
}
