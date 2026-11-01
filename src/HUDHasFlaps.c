// ?HUDHasFlaps@@YIDXZ @ rva 0xabc0 (11 B + 5 pad) — cmp byte [hud+0x24d],0x20 /
//   setne al / ret.  Fastcall, no params; char return keeps AL-only (wave-5
//   d62 char-return rule; int return emitted 33 c0 head — probe 01c).
//   map: hudFlagQ=_hud+0x24d (human-coin interior offset from mapgen)
extern char hudFlagQ[];

char __fastcall HUDHasFlaps(void)
{
    return hudFlagQ[0] != 0x20;
}