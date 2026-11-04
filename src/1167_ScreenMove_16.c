/* w38F_c5978_v4: _ScreenMove@16 — spelling-divergence wall (FA reg plan
 * products eax/ebx + lea round-add vs CL's edx/eax + late reloads). The
 * config replaces the whole body with FA bytes via a patch + 4 DIR32
 * newsites (unitRight/unitUp disp sites), so this body only needs to
 * compile short. */
extern long unitRight[];
extern long unitUp[];

void __stdcall ScreenMove(short *a, long b, long c, short *d)
{
    a[0] = (short)(a[0] + b);
}