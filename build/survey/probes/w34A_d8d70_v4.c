/* w34A_d8d70 v4: merged ||-chain with the shared-fail-tail shape
 * (cookbook "merged || chains"): one branchy bool, if() ... return 1.
 */
int w34A_d8d70_v4(long **pp)
{
    long *er = *pp;
    if (er[0] != 0xe06d7363 || er[4] != 3 || er[5] != 0x19930520
        || er[7] != 0)
        return 0;
    return 1;
}