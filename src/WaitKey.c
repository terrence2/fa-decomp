/* _WaitKey @ rva 75456 (0x126c0, 48 B) — plain C.
 * IAT-loaded fn-ptr parked in esi (8b 35 [__imp__Sleep]) is what unlocks
 * FA's form: with the pointer local declared FIRST as
 * `SleepFn sp = impSleepIAT`, CL plans esi/park + ff d6 call instead of
 * materializing ff 15 (probe w14a_wk2 note about imp-IAT loads). The
 * counter must NOT be ++ — `waitCounter = waitCounter + 1;` reproduces
 * FA's a1/40/a3 mov-test-store reg-inc dance (naked version claimed this
 * was asm-only; the esi park was the missing lever, not the counter).
 *
 * probes: build/survey/probes/w23_WaitKey_v1.c (EXACT) and _v2.c (EXACT —
 *   volatile counter variant; v1 preferred as it adds no volatile)
 *   run: python3 build/survey/hybrid_probe.py build/survey/probes/w23_r1.json
 *
 * maps copied verbatim from tools/swap.json entry WaitKey:
 *   _impSleepIAT=__imp__Sleep
 */
typedef void (__stdcall *SleepFn)(unsigned long);
extern SleepFn impSleepIAT;
extern unsigned long waitCounter;
extern int GetKey(void);

int WaitKey_q(void)
{
    SleepFn sp = impSleepIAT;
    int r;
    for (;;) {
        r = GetKey();
        if (r)
            return r;
        waitCounter = waitCounter + 1;
        sp(0);
    }
}