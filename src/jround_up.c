/* jround_up - FA rva 0x74f40 (479040) - EXACT probe verdict, tier1_a_r2.json entry 'jround_up_v6'
 * Form: patch-hybrid
 * Levers: 2 1-byte patches over plain C
 * Maps: (none)
 * patch 0x1: ->4c
 * patch 0xb: ->0e
 * Probes: v1-v7
 */
long jround_up(long a, long b)
{
    long t = a + b - 1;
    return t - t % b;
}
