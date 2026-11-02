/* COBv - FA rva 0x76d70 (486768) - EXACT probe verdict, tier1_a_r1.json entry 'COBv_v1'
 * Form: plain C
 * Levers: rep-movsd static return via pointer-array extern
 * Maps: _packetTicks=?packetTicks@@3PAJA
 * Probes: v1
 */
extern long packetTicks;
extern char curThing[];
extern char curThingType[];
extern void *memcpy(void *, const void *, unsigned);

int __stdcall COBv(void)
{
    char *bank = (char *)&packetTicks + 0x4e8;
    memcpy(bank, curThingType + 0xca, 24);
    *(unsigned short *)(bank + 2) = *(unsigned short *)(curThing + 0x245);
    return (int)bank;
}
