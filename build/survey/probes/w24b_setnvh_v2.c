/* probe v1: set-new-handler lock/unlock swap; arg load late-ish */
typedef int (__cdecl *PNH)(unsigned int);
extern PNH pnhH;                /* obj __pnhH -> ?_pnhHeap@@3P6AHI@ZA */
extern void _lock_a(int n);     /* obj __lock_a -> __lock */
extern void _unlock_a(int n);   /* obj __unlock___a -> __unlock */


PNH _setnq(PNH pnh)
{
    PNH old;
    _lock_a(9);
    old = pnhH;
    pnhH = pnh;
    _unlock_a(9);
    return old;
}
