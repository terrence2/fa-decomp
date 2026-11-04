// $FA$_t_47ba40 v2 — LMultDiv256 arg2 declared short (caller passes the
// raw 16-bit in dx: FA 66 8b 15, not movsx); v<0 branch spells t = t + v
// (FA: add eax,ecx / mov [esi],eax / test eax,eax) and >= branch
// v = v - t (FA: sub ecx,eax / mov [esi],ecx / jns).
extern short serviceTicks;
extern long __fastcall LMultDiv256(long a, short b);

void __fastcall w43b_decay(long *p)
{
    long t;
    long v;
    t = abs(*p) / 2;
    if (t < 0x100)
        t = 0x100;
    else if (t > 0x4000)
        t = 0x4000;
    t = LMultDiv256(t, serviceTicks);
    v = *p;
    if (v < 0) {
        t = t + v;
        *p = t;
        if (t > 0)
            *p = 0;
    } else {
        v = v - t;
        *p = v;
        if (v < 0)
            *p = 0;
    }
}