// @MMFreePtr@4 @ rva 0x35b70 — test ecx,ecx / jz ret / call @MMPtrToHandle@4
//   / mov ecx,eax / jmp @MMFreeHandle@4 (tail call) / ret. CL tail-jmps the
//   void call as the if-body's last statement (probe w5_freea exact).
extern void *__fastcall MMPtrToHandle(void *p);
extern void __fastcall MMFreeHandle(void *h);

void __fastcall MMFreePtr(void *p)
{
    if (p)
        MMFreeHandle(MMPtrToHandle(p));
}
