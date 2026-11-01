// ?CheckItem@@YIXDG@Z @ rva 0xcb60 (32 B) — void __fastcall CheckItem(char
// state, unsigned short id) for the dialog/menu item at _enableHelper's
// result. Spills state into bl across the helper call (ecx=id fed to the
// unnamed helper at $FA$_t_40cb80), then test eax,eax / je skip, and stores
// 0x1e/0x1f at [item+0x12] via the cmp bl,1 / sbb cl,cl / add cl,0x1f
// borrow chain. The -1/0 ternary arm pair is what makes CL 4.2 emit SBB
// (sete/setl forms lose); the &0xff cast pins the UNSIGNED byte compare —
// both needed (probe w13c_chk2/chk3/chk7/chk8 lose, w13c_chk5 exact).
extern int __fastcall itemHelper4(unsigned short id);

void __fastcall CheckItem_q(char a, unsigned short b)
{
    int v = itemHelper4(b);
    if (v != 0)
        *(unsigned char *)(v + 0x12) = ((a & 0xff) < 1 ? -1 : 0) + 0x1f;
}