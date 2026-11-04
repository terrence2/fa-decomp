/* @G_HFlipBitmap@4 @ rva 0xb4cc0 — patch-hybrid (tier-0/Tier-3): plain C +
 * 3 patches. Byte-swap each row of a bitmap (W at +2, H at +6, base +0xa).
 *
 * patch 0xf: CL hoists the [ecx+0xa] base load above the row-counter setup
 * and multiplies w-in-esi x y-in-edi (FA: y-in-esi x w-in-eax with the base
 * add FOLDED: mov esi,edi; imul esi,eax; add esi,[ecx+0xa]; lea
 * eax,[eax+esi-1] — CL never folds the add while ecx stays live across the
 * loop). Patch replaces CL[0xf,0x14) (8b 51 0a / 8b f0 / 0f af f7 / 03 f2 /
 * 8d 44 06 ff, 14 B) with FA's 12 B 8b f7 / 0f af f0 / 03 71 0a / 8d 44 30
 * ff — net -2 B; all later jcc disp values recheck.
 * patch 0xa: jle disp 0x2b->0x29 (skip-target pop edi shifts -2 with the
 * region patch): 7e 29.
 * patch 0x33: (post-patch-1 position) outer-loop jg becomes 7f d7 (target
 * 0x0c, next 0x35): 7f d7.
 * v5's C lever: row counter declared via a pointer first (register-role
 * lever — FA parks i in edi, lo in esi; v4 matched the roles but still
 * hoisted the base load). probe count v1-v7.
 *
 * probes: v1-v4 (no: role/multiply-order swaps), v5-v7 (no: hoist),
 *   build/survey/probes/G_HFlipBitmap_v5.c + patches — run: python3
 *   build/survey/hybrid_probe.py build/survey/probes/tier0_r7.json
 *   (HFlip_v5h EXACT).
 *
 * entry JSON for tools/swap.json:
 *   {"rva": 740544, "obj": "G_HFlipBitmap", "src": "src/G_HFlipBitmap.c",
 *    "maps": [],
 *    "patch": ["0xf,14,8bf70faff003710a8d4430ff", "0xa,2,7e29", "0x33,2,7fd7"]}
 */
void __fastcall G_HFlipBitmap_m(char *bm)
{
    char *lo;
    long off;
    long i = 0;
    while (i < *(long *)(bm + 6)) {
        long w = *(long *)(bm + 2);
        off = w * i;
        lo = (char *)(off + *(long *)((char *)bm + 10));
        {
            char *hi = lo + w - 1;
            while ((unsigned long)hi > (unsigned long)lo) {
                char t;
                t = *lo;
                *lo = *hi;
                *hi = t;
                lo = lo + 1;
                hi = hi - 1;
            }
        }
        i = i + 1;
    }
}