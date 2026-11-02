/* ConvertOldPreferredTargetId - FA rva 0x800f0 (524528) - EXACT probe verdict, tier1_a_r2.json entry 'ConvertOldPreferredTargetId_v5'
 * Form: patch-hybrid
 * Levers: 1-byte patch; v6 spelling was worse
 * Maps: (none)
 * patch 0x9: ->c4
 * Probes: v1-v6
 */
long __fastcall ConvertOldPreferredTargetId(unsigned short id)
{
    long r = id & 0x1fff;
    if (id & 0x1000)
        r |= -0x2000;
    r &= 0x1fffffff;
    if (id & 0x2000)
        r |= 0x20000000;
    if (id & 0x4000)
        r |= 0x40000000;
    if (id & 0x8000)
        r |= 0x80000000;
    return r;
}
