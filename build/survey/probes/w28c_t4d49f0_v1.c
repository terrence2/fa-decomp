// 0xd49f0 gap chunk (23 B) — v1
extern void __cdecl w28c_cfltcvtInit(void);
extern unsigned long __cdecl w28c_p5TestFdiv(void);
extern void __cdecl w28c_setDefPrec(void);
extern unsigned long w28c_adjustFdiv;

void __cdecl w28c_t4d49f0(void)
{
    w28c_cfltcvtInit();
    w28c_adjustFdiv = w28c_p5TestFdiv();
    w28c_setDefPrec();
    __asm { fnclex }
}
