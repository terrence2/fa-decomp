/* w33B_43f90_c3.c -- 16-B forwarder thunk at 0x43f90: plain C with one fastcall
   extern (@4 = 4 total param bytes = one dword => ecx-set + edx passthrough) */
extern void __fastcall w33b_mmp1(void *p2);

void __cdecl w33b_43f90(int p1, void *p2, int p3)
{
    w33b_mmp1(p2);
}