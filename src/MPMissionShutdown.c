// ?MPMissionShutdown@@YGXXZ @ rva 0x6b6c0 (32 B) — FA asm: a1 [thisComputer] /
//   test eax,eax / jle L / a1 [packetTicksAdjust+0x20] / a3 [gamePrefs] / L: ret.
//   Plain C with a TO-addend map: packetTicksAdjust+0x20 is reached as a single
//   a1 moffs load via an extern long[] base symbol mapped at +0x20 (MSGHide/
//   buffRemapTbl80 family) — indexing the extern with constant 0 keeps the
//   reloc on the base so the +0x20 lands in the map TO.
extern long thisComputer;
extern long gamePrefs;
extern long packetTicks8[];   // -> ?packetTicksAdjust@@3PAJA+0x20

void __stdcall MPMissionShutdown_q(void)
{
    if (thisComputer > 0)
        gamePrefs = packetTicks8[0];
}