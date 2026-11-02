// v3: param reassign in place — imul cx,cx (param container), copy x to si
// before the arg clobbers ecx, lea ecx,[esi*2] for the arg, sub ax,si.
extern short __fastcall Rand(int x);

short __fastcall w30g_randrange3(short x)
{
    x = x * 0xb6;
    return Rand(x * 2) - x;
}