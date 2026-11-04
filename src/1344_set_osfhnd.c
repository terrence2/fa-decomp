/* w45F __set_osfhnd @ 0x4deb40 (164 B, FPO 2 params) — v1 husk for
 * full-body transplant (w38G_debf0 recipe, mirror of 0xdebf0's convert):
 * FA: nhandle guard-first (39 0d cmp [__nhandle],ecx; jbe fail), slot row
 * via (fh&~0x18)>>3 + __crtheap+0x4, entry = (fh&0x1f)<<2*9, oshandle==-1
 * gate, __aexit_rtn+8==1 gate, 0/1/2 SetStdHandle(0xfffffff6/f5/f4, fh)
 * dispatch with eb_jmp merge (value = fh itself, pushed at each case),
 * sib store [row]=fh, return 0. fail: errno=9 via __errno, dos = 0 via
 * $FA$_t_4d99c0, return -1.
 * patch: 0x0,<len>,<164 FA bytes, reloc dwords and rel32 disps zeroed>
 *   + newsites 0x8/0x19/0x32/0x52/0x61/0x70 (6=DIR32),
 *   0x86/0x91 (20=REL32, disp START; e8 at 0x85/0x90). */
extern unsigned long w45f_nhl;                 /* -> __nhandle */
extern char w45f_pio2[];                       /* -> __crtheap+0x4 */
extern unsigned long w45f_aex8;                /* -> __aexit_rtn+0x8 */
extern int *__cdecl w45f_ern(void);            /* -> __errno */
extern void __cdecl w45f_den(void);            /* -> $FA$_t_4d99c0 */
__declspec(dllimport) int __stdcall SetStdHandle(long, void *);

int __cdecl w45f_soh(int fh, long value)
{
    return 0;
}