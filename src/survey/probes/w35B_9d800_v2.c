/* w35B: unnamed 0x9d800 (48 B) — v2
 * v1 block1 was byte-EXACT; the second half merged v==0x13/v==0x14 into a
 * sete and reloaded the global 3 extra times (CL restructured my separate
 * ifs). v2 uses the merged ||-chain recipe (shared true-tail branchy bool)
 * with the single reload spelled first.
 */
extern unsigned char curE3[];   /* _curThing+0xe3 */

unsigned char __cdecl w35b_state(void)
{
    unsigned char v = curE3[0];
    if (v >= 1 && v <= 0x12)
        return 0;
    v = curE3[0];
    if (v < 0x13 || v > 0x1e || v == 0x13 || v == 0x14)
        return 1;
    return 0;
}