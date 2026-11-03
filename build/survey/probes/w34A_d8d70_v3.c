/* w34A_d8d70 v3: &&-chain over a volatile-typed record pointer — v2's
 * non-volatile chain let CL load each field into ecx before the compare;
 * FA compares the MEMORY operands directly (83 78 10 / 81 78 14 / 83 78 1c).
 */
int w34A_d8d70(volatile long **pp)
{
    volatile long *er = *pp;
    return er[0] == 0xe06d7363 && er[4] == 3
           && er[5] == 0x19930520 && er[7] == 0;
}