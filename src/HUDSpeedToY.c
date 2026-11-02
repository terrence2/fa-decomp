// ?HUDSpeedToY@@YIJJ@Z @ rva 0x7c20 (32 B) — hud-relative speed->y mapping.
// FA: eax=[hud+0x310]; sub eax,ecx(arg); ecx=[hud+0x32c] cached for the add;
// imul eax,[hud+0x209]; cdq; idiv [hud+0x205]; add eax,ecx; ret. All four
// _hud field reads; hud is the FA.SMS identity (wave-16/19 a1-moffs band).
extern char hud[];

long __fastcall HUDSpeedToY(long spd)
{
    long r;
    long acc;

    r = *(long *)(hud + 0x310) - spd;
    acc = *(long *)(hud + 0x32c);
    return acc + r * *(long *)(hud + 0x209) / *(long *)(hud + 0x205);
}