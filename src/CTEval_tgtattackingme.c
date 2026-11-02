/* CTEval_tgtattackingme - FA rva 0x64050 (409680) - EXACT probe verdict, tier1_a_r4.json entry 'CTEval_tgtattackingme_v4'
 * Form: patch-hybrid
 * Levers: all-goto shared exits + uchar cast (jb); appended second 33 c0 c3 exit block
 * Maps: (none)
 * patch 0x9: -> 32
 * patch 0x12: -> 29
 * patch 0x3c: 4 B append 33 c0 c3 90 (second exit block)
 * Probes: v1-v4
 */
extern char serviceTicks[];
extern unsigned short curId;

long CTEval_tgtattackingme(void)
{
    char *t;
    if (!*(unsigned short *)(serviceTicks + 0x20))
        goto L1;
    if (!serviceTicks[0xe8])
        goto L1;
    t = *(char **)(serviceTicks + 0xf4);
    if ((unsigned char)*(char *)(t + 0xe3) < 0x20)
        goto L1;
    if (*(unsigned short *)(t + 0xee) != curId)
        goto L1;
    return 1;
L1:
    return 0;
}
