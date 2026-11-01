// @FMFuelConsumption@4 @ rva 0x51470 (48 B) — pct>100 returns the word at
// _curThingType+0x163 << 8; else word at +0x161 * pct << 8 / 100 (movsx,
// imul ecx, shl, cdq/idiv reusing ecx=100). probe w12a_09 byte-exact.
extern short fuelLo;
extern short fuelHi;

long __fastcall FMFuelConsumption_q(long pct)
{
    if (pct > 100)
        return (long)fuelLo << 8;
    return ((long)fuelHi * pct * 256) / 100;
}
