/* gap chunk rva 0x64fc0 (32 B): cdecl — clamp lim into [COMaxSpeed, COMinSpeed].
   FA: push esi / call $FA$_t_464c90 / mov esi,eax / call COMinSpeed /
   cmp eax,esi / jg ret / call COMaxSpeed / cmp eax,esi / jl ret /
   mov eax,esi / pop esi / ret. */
extern int COMinSpeed(void);              /* _COMinSpeed@0 */
extern int COMaxSpeed(void);              /* _COMaxSpeed@0 */
extern int __cdecl w30b_t40(void);        /* $FA$_t_464c90 */

int w30b_spdclamp(void)
{
    int lim = w30b_t40();
    int lo = COMinSpeed();
    int hi;
    if (lo > lim)
        return lo;
    hi = COMaxSpeed();
    if (hi < lim)
        return hi;
    return lim;
}