// v5: Rand declared short fastcall(short) — word arg still counts @4 in the
// mangle; CL passes the short in ecx without a widen, lea ecx,[esi*2].
extern short __fastcall Rand(short x);

short __fastcall w30g_randrange5(short x)
{
    x = x * 0xb6;
    return Rand(x * 2) - x;
}