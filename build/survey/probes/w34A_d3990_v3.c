/* w34A_d3990 v3: identical v2 C; expects the two 4-B cmp/jcc byte patches
 * (CL canonicalizes pointer relational operand order: cmp iter,bound; jae
 * for both lo<hi and hi>lo spellings; FA = cmp bound,iter; jbe/ja).
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