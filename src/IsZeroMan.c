// __IsZeroMan @ rva 0xdfa40 (29 B, no pad) — man-dblock all-zeros test
// CONVERTED (survey closeout wave t4, 2026-11-02). Old wall notes were
// WRONG about the ABI: FA does NOT take the param in ecx by convention —
// the chunk loads it from the stack (8b 4c 24 04 mov ecx,[esp+4], __cdecl)
// and CL's register plan for a walking-loop test matches FA exactly from
// plain C: param->ecx, strength-reduced walking pointer stays in ecx,
// counter in eax. Old probes (d88/d112/d115) failed on different spellings
// (param-to-eax load-then-test).
// Sole residual divergence: load-folds-to-test wall (tier-0 family 1) —
// CL emits mov edx,[ecx]/test edx,edx (8b 11/85 d2, 4 B) for *p != 0 where
// FA cmp-tests mem-immediate 83 39 00 (3 B), shifting the jl disp f1->f2.
// Volatility is a no-op lever here (t4_zero_v1/v2/v3 all identical: a plain
// mov+test IS a single access, so the optimizer gains nothing).
// C form + 2 patches:
//   patch 6,4,833900 — the mem-test rewrite (4->3 B);
//   patch 18,2,7cf2 — retarget the loop back-jump after the 1-B shrink
//     (offsets are post-previous-patch positions: 0x12 is post-patch 1).
// Probes: d88/d112/d115/d117 asm; t4_zero_v4 EXACT (0 relocs, no tail).
int IsZeroMan_zr(long *p)
{
    int i;

    for (i = 0; i < 3; i++)
        if (p[i])
            return 0;
    return 1;
}