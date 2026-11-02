/* @OBJStopAdding@0 @ rva 0x8f480 — plain C (tier-0 re-read).
 * FA: r = MMRealloc(wngStopTop, cmStopTop - wngStopTop); if (r) wngStopTop = r.
 * v3's key lever: the globals are declared as plain VALUES (extern unsigned
 * long cmStopTop) — v1/v2 typed them as pointers/arrays and CL emitted an
 * extra deref (8b 0d + 8b 00) that FA doesn't have. The call is fastcall with
 * two stack args (push order wngStopTop first); __stdcall + int casts keep
 * CL's plan.
 *
 * probes: build/survey/probes/OBJStopAdding_v1.c (no), _v2.c (no), _v3.c
 *   (EXACT) — run: python3 build/survey/hybrid_probe.py
 *   build/survey/probes/tier0_r3.json
 *
 * maps (unchanged): _cmStopTop=?COMMENT_TYPE@@3W4__unnamed@@A+0x858
 *                   _wngStopTop=?wingSay@@3PAUSAY@@A+0xe64
 */
extern unsigned long cmStopTop;
extern unsigned long wngStopTop;
extern void *__fastcall MMReallocPtr(int a, int b);

void __stdcall OBJStopAdding_k(void)
{
    unsigned long r;
    r = (unsigned long)MMReallocPtr((int)wngStopTop,
                                    (int)(cmStopTop - wngStopTop));
    if (r)
        wngStopTop = r;
}