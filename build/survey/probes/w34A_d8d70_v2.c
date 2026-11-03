/* w34A_d8d70 v2: &&-chain with positive conditions -> FA's shape
 * (cmp / jne shared tail, mov eax,1/ret before the xor/ret exit). v1's
 * early-return-0 spellings produced three inline 33 c0 c3 exits.
 */
int w34A_d8d70(long **pp)
{
    long *er = *pp;
    return er[0] == 0xe06d7363 && er[4] == 3
           && er[5] == 0x19930520 && er[7] == 0;
}