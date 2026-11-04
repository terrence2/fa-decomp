// 0x1df90 = 122768, unnamed gap, 16 B (5 code e9 + 11 census pad)
// FA asm: e9 2bfcffff  jmp ?Destroy@CDirDraw@@QAEXXZ  (+ census pad),
// 1 rel32 ref from ?DeleteSingleton@CDirDraw@@SAXXZ.  Plain C stdcall
// wrapper emitted push/call/ret4 (w25c_fwdDestroy_v1) — CL 4.2 does NOT
// same-layout-merge this tail -> naked asm pure jmp.
extern void __stdcall DDDestroyQ(void *p);
/* map _DDDestroyQ=?Destroy@CDirDraw@@QAEXXZ */

__declspec(naked) void __stdcall w25c_fwdDestroy_q(void *p)
{
    __asm { jmp DDDestroyQ }
}