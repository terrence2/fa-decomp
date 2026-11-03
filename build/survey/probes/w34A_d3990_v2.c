/* w34A_d3990 v2: spell the conditions as (hi > lo) so CL emits
 * cmp edi,esi / jbe + cmp edi,esi / ja (FA's operand order, found by
 * v1's diff at 0xb-0xc and 0x1a-0x1b: CL's `lo < hi` canonicalizes to
 * cmp esi,edi).
 */
void __cdecl w34_d3990(long **lo, long **hi)
{
    if ((unsigned long)hi > (unsigned long)lo) {
        do {
            void *fn = *lo;
            if (fn != 0)
                ((void (__cdecl *)(void))fn)();
            ++lo;
        } while ((unsigned long)hi > (unsigned long)lo);
    }
}