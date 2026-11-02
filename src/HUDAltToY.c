// ?HUDAltToY@@YIJJ@Z @ rva 0x8170 (32 B) — hud altitude->y mapping, twin of
// w6 HUDSpeedToY (rva 0x7c20, same schedule). FA: eax=[lastWC+0x1c];
// sub eax,ecx(arg); ecx=[hud+0x32c] cached for the add; imul eax,[hud+0x226];
// cdq; idiv [hud+0x222]; add eax,ecx; ret.  (0x22a/0x226 were 4 high —
// HUDAltToY's own chunk bytes: imul [0x51ce36] idiv [0x51ce32], hud@0x11cc10.) 2nd fastcall arg (edx) unused.
extern char qwc[];   /* ?lastWasInQuickCreator@@3DA+0x1c */
extern char hud[];

long __fastcall HUDAltToY(long alt, long altUnused)
{
    long r;
    long acc;

    r = *(long *)qwc - alt;
    acc = *(long *)(hud + 0x32c);
    return acc + r * *(long *)(hud + 0x226) / *(long *)(hud + 0x222);
}
