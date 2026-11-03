/* w33B_43f90_c2.c -- v2: naked asm thunk (MASM-only encoding class) */
extern void __fastcall w33b_mmp3(int a, int b, int c);

void __declspec(naked) w33b_43f90(void)
{
    __asm {
        mov ecx, [esp+8]
        jmp w33b_mmp3
    }
}