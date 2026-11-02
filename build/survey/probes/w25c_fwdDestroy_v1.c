// 0x1df90 = 122768, unnamed gap, 16 B (5 code + 11 pad) — pure e9 jmp to
// ?Destroy@CDirDraw@@QAEXXZ (thiscall void(void*), no rel32 refs beyond
// ?DeleteSingleton).  Same-convention tail: try plain C first.
extern void __stdcall DDDestroyQ(void *p);
/* map _DDDestroyQ=?Destroy@CDirDraw@@QAEXXZ */

void __stdcall w25c_fwdDestroy_q(void *p)
{
    DDDestroyQ(p);
}