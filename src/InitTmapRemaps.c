// ?InitTmapRemaps@@YIXXZ @ rva 0xb0b30 (32 B) — FA asm (fastcall, 0 args):
//   57/33 c0/bf <?palBlackenDest@@3FA+0x8> (table start imm32)/b9 0x843
//   (1347 dwords)/f3 ab (rep stosd inline memset)/5f/a3 <_currentLayer+0x160>
//   (the xor'd eax re-stored via a3)/c3.  Plain C exact: CL 4.2 INLINES
//   memset(t, 0, 0x210c) as push edi/mov edi,imm/mov ecx,imm/rep stosd/pop edi,
//   and the following 0 store re-uses eax as a3.  Probe
//   build/w4probe/w19_inittmap_v1.obj — exact.
extern char tmapRemapTbl[];   /* ?palBlackenDest@@3FA+0x8, 0x210c B */
extern long tmapLayerBase;    /* _currentLayer+0x160 */

extern void *memset(void *, int, unsigned);

void __fastcall InitTmapRemaps_f(void)
{
    memset(tmapRemapTbl, 0, 0x210c);
    tmapLayerBase = 0;
}