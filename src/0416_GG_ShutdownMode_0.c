/* @GG_ShutdownMode@0 @ rva 381664 (0x5d2e0, 48 B) — plain C.
 * thiscall-style shutdown: esi park of ggpSrf, Destroy call, release, and
 * the c7 05 lpPrimarySurface=NULL store scheduled BETWEEN the release call
 * and its add esp,4. CL reaches FA's plan with (1) the surface local `s`
 * declared first (esi park), (2) the global store written as its own
 * statement AFTER the cdecl call — CL schedules the store into the
 * arg-cleanup region (SER_ProcessDataPacket precedent), and (3) ggFree as
 * a plain cdecl extern so the arg push comes from esi.
 *
 * probes: build/survey/probes/w23_GG_ShutdownMode_v1.c (EXACT; the v2
 *   tree-split variant put ggRelease's target in ecx and failed)
 *   run: python3 build/survey/hybrid_probe.py build/survey/probes/w23_r1.json
 *
 * maps copied verbatim from tools/swap.json entry GG_ShutdownMode:
 *   _ggpSrf=?lpPrimarySurface@@3PAVCDirDrawSurface@@A
 *   @ggRelease@4=$FA$_t_4779a0
 *   _ggFree=$FA$_t_4d4880
 */
extern long ggpSrf;
extern void __fastcall ggRelease(long o);
extern void __cdecl ggFree(long p);

void GG_ShutdownMode_q(void)
{
    long s = ggpSrf;
    if (s) {
        ggRelease(s);
        ggFree(s);
        ggpSrf = 0;
    }
}