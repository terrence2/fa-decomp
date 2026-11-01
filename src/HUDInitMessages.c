// _HUDInitMessages@0 @ rva 0x5bf0 — three zero stores clearing HUD message
//   links: unitRight+0x10, hud+0xa18, unitUp+0x10
extern char unitRight[];
extern char hud[];
extern char unitUp[];
void __stdcall HUDInitMessages_q(void)
{
    *(long *)(unitRight + 0x10) = 0;
    *(long *)(hud + 0xa18) = 0;
    *(long *)(unitUp + 0x10) = 0;
}
