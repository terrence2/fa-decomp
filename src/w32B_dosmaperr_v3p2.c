/* wave 32 batch B: __dosmaperr v3 (0x4d9930, 115 B)
   v2 + unsigned two-way range casts (jb/ja not jl/jg).              */

int *_w32b_dz(void);                       /* $FA$_t_4d99c0 */
int *_errno(void);                          /* -> __errno */
extern int __cfltcvt_tab[];

void w32b_dosmaperr(int oserrno)
{
    int *pa;
    int i;

    *_w32b_dz() = oserrno;
    i = 0;
    pa = (int *)((char *)__cfltcvt_tab + 0x18);
    do {
        if (*pa == oserrno) {
            *_errno() = *(int *)((char *)__cfltcvt_tab + 0x1c + 8 * i);
            return;
        }
        pa += 2;
        i++;
    } while (pa < (int *)((char *)__cfltcvt_tab + 0x180));
    if ((unsigned)oserrno >= 0x13 && (unsigned)oserrno <= 0x24) {
        *_errno() = 0xd;
        return;
    }
    if ((unsigned)oserrno >= 0xbc && (unsigned)oserrno <= 0xca) {
        *_errno() = 8;
        return;
    }
    *_errno() = 0x16;
}

/* provenance (probed as w32B_dosmaperr_v3p2):
   patch 0x0: toolchain-diff CL load-then-cmp (8b10/3bd1) deleted at loop head
   patch 0x13: toolchain-diff FA folded cmp [eax],ecx (3908) inserted 2 B
   patch 0x21: toolchain-diff jb back-edge disp stale after -2 B shrink (ef->f1)
   patch 0x25: toolchain-diff signed jl (7c) vs FA unsigned jb (72)
   patch 0x2a: toolchain-diff signed jg (7f) vs FA unsigned ja (77)
   patch 0x7f: toolchain-diff signed jl (7c) vs FA unsigned jb (72)
   patch 0x87: toolchain-diff signed jg (7f) vs FA unsigned ja (77)      */
