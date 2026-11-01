// @MMLockR@8 @ rva 0x35d60 (16 B) — same shape as MMLock/MMLockW
//   (callee reads ecx only; our edx stays untouched)
extern int __stdcall MMAccessE(int, int, int);

int __fastcall MMLockR(int a, int b)
{
    return MMAccessE(a, 0, 0);
}
