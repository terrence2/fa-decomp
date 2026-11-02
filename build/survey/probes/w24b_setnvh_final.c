// ?_set_new_handler@@YAP6AHI@ZP6AHI@Z@Z @ rva 0xdf590 (914832) — FA 40 B:
//   56                  push esi                (fpo/esp, prolog=1, regs=1)
//   6a 09               push 9
//   e8 ....             call __lock
//   8b 44 24 0c         mov eax,[esp+0xc]        (the arg, push 9 outstanding)
//   83 c4 04            add esp,4
//   8b 35 ....          mov esi,ds:[_pnhHeap]    (old handler)
//   6a 09               push 9
//   a3 ....             mov ds:[_pnhHeap],eax    (install new)
//   e8 ....             call __unlock
//   83 c4 04            add esp,4
//   8b c6 5e c3         mov eax,esi / pop esi / ret
// i.e. _set_new_handler(pnh): __lock(9); old=_pnhHeap; _pnhHeap=pnh;
// __unlock(9); return old. EXACT fit (byte-verify PASS, no tail-accept;
// no pad). Raw CL (w24b_setnvh_v2.obj, 40 B) has ONE delta: it orders
// 'mov [_pnhHeap],eax' BEFORE the second 'push 9' where FA pushes the
// __unlock(9) arg first. One same-length reorder patch swaps the two
// (the a3 disp keeps its DIR32 via SITE:TYPE:SYMBOL):
//   --patch '0x15,7,6a09a300000000,3:6:_pnhH'
//
// fitobj (winning command):
//   python3 tools/fitobj.py build/survey/probes/w24b_setnvh_v2.obj 914832 \
//     --map '__lock_a=__lock' --map '__unlock_a=__unlock' \
//     --map '_pnhH=?_pnhHeap@@3P6AHI@ZA' \
//     --patch '0x15,7,6a09a300000000,3:6:_pnhH' \
//     build/survey/probes/w24b_setnvh_final_fit.obj
//
// Patch provenance: 0x15,7 — state toolchain-diff — CL schedules the store
// before the push; FA pushes the pending arg first. Byte shape otherwise
// identical, incl. 'mov eax,[esp+0xc]' taken with push 9 (8 B) outstanding.
// Maps: C-level `_lock_a`/`_unlock_a` decorate to obj `__lock_a` etc and
// retarget FA's own __lock/__unlock chunks; the global pnhHeap is FA's
// ?_pnhHeap@@3P6AHI@ZA (data chunk @ 0x188ba8, VA 0x588ba8 — matches FA's
// a3/8b35 sites).
typedef int (__cdecl *PNH)(unsigned int);
extern PNH pnhH;                /* _pnhH -> ?_pnhHeap@@3P6AHI@ZA */
extern void _lock_a(int n);     /* __lock_a -> __lock */
extern void _unlock_a(int n);   /* __unlock_a -> __unlock */

PNH _setnq(PNH pnh)
{
    PNH old;
    _lock_a(9);
    old = pnhH;
    pnhH = pnh;
    _unlock_a(9);
    return old;
}
