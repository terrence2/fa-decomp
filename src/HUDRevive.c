// _HUDRevive@0 @ rva 0x66a0 (48 B) — zero the HUD TV-replay scratch state.
// FA: mov byte[hud+0x628],1 (c6 05, HIGHLOW site — hud[] identity ref);
// xor eax,eax then 6 stores through ax/eax/al (word _dirTVZ, dword
// ?lastWasInQuickCreator@@3DA+0x44, word _dirTVY, byte _onTVZ/_onTVY and
// ?lastWasInQuickCreator@@3DA+0x20), ret. w21a: interior sites of the
// ?lastWasInQuickCreator@@3DA chunk need two TO-addend maps.
extern char hud[];
extern short dirTVZ;
extern short dirTVY;
extern char onTVZ;
extern char onTVY;
extern long lastWasInQC44;   /* ?lastWasInQuickCreator@@3DA+0x44 */
extern char lastWasInQC20;   /* ?lastWasInQuickCreator@@3DA+0x20 */

void __stdcall HUDRevive(void)
{
    hud[0x628] = 1;
    dirTVZ = 0;
    lastWasInQC44 = 0;
    dirTVY = 0;
    onTVZ = 0;
    onTVY = 0;
    lastWasInQC20 = 0;
}