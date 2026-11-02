// unnamed chunk @ rva 0x50970 (32 B) — fastcall(short): cx *= 0xb6 / t=si /
// lea ecx,[esi*2] / call @Rand@4 / sub ax,si / ret. Rand returns short in ax.
// wave-5 idiom: 16-bit params stay in the 16-bit half of the arg register.
extern short __fastcall Rand(int x);

short __fastcall w30g_randrange(short x)
{
    short t;
    t = x * 0xb6;
    return Rand(t * 2) - t;
}