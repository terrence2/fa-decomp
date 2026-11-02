/* ?Wait@@YAHXZ @ rva 71568 (0x11790, 32 B) — plain C.
 * FA's shared-ret shape: `if (WaitKey() == 'q') ErrorExit(0);` in an int
 * function with NO return statement — CL passes the WaitKey value through
 * in eax on the fallthrough (jne) and ErrorExit's on the taken path; both
 * paths land on the shared c3. The w14a_wait3 naked note was wrong about
 * liveness: 'k live across the ErrorExit call' (esi homing) only appears
 * if the result is named; the unnamed single call keeps eax untouched.
 * __declspec(noreturn) is NOT needed (C2485 on CL 4.2); an empty int
 * function body after the if does the job.
 *
 * probes: build/survey/probes/w23_Wait_v1.c (EXACT)
 *   run: python3 build/survey/hybrid_probe.py build/survey/probes/w23_r1.json
 *
 * maps: none (entry has no maps in tools/swap.json either; WaitKey/
 *   ErrorExit resolve from their own stubs)
 */
extern int WaitKey(void);
extern void __cdecl ErrorExit(long code);

int Wait_q(void)
{
    if (WaitKey() == 0x71)
        ErrorExit(0);
}