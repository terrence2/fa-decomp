// _CTEval_betterspeed @ rva 0x64620 — CTVarDiff((int)COMaxSpeed) >= 0x4b with
//   a pre-materialized bool (xor ecx,ecx before the cmp — probe d50; the plain
//   return drops the zeroing, d51).
extern int CTVarDiff(int v);
extern int COMaxSpeed(void);

int CTEval_betterspeed_q(void)
{
    int b = 0;
    int r = CTVarDiff((int)COMaxSpeed);
    b = r >= 0x4b;
    return b;
}
