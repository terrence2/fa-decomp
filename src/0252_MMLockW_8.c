// @MMLockW@8 @ rva 0x35d50 (16 B) — same shape as MMLock
extern int __stdcall MMAccessE(int, int, int);

int __fastcall MMLockW(int a, int b)
{
    return MMAccessE(a, 0, 0);
}
