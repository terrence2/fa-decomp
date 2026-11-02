/* validate_packet - FA rva 0xadef0 (712432) - EXACT probe verdict, tier1_a_r4.json entry 'Validate_packet_v3'
 * Form: patch-hybrid
 * Levers: 1 patch: dword-load + word-compare spelling (66 8b 08 / 66 83 f9 1c)
 * Maps: (none)
 * patch 0x4: 4->7 B 66 8b 08 66 83 f9 1c
 * Probes: v1-v3
 */
unsigned char validate_packet(void *p)
{
    unsigned short v, w;
    v = *(unsigned short *)p;
    if (v >= 0x1c)
        goto Lf;
    w = *(unsigned short *)((char *)p + 2);
    if (w < 4)
        goto Lf;
    if (w > 0x404)
        goto Lf;
    return 1;
Lf:
    return 0;
}
