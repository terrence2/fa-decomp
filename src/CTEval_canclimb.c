/* CTEval_canclimb - FA rva 0x64540 (410944) - EXACT probe verdict, tier1_a_r1.json entry 'CTEval_canclimb_v6'
 * Form: plain C
 * Levers: plain C; early-guard return shape
 * Maps: _COMinSpeed=_COMinSpeed@0
 * Probes: v1-v6
 */
extern char curThing[];
extern int COMinSpeed(void);

long CTEval_canclimb6(void)
{
    return (*(int *)(curThing + 0x34) >> 8) >= COMinSpeed() + 0x4b;
}
