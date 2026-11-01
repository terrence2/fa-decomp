// @MMAccessR@4 @ rva 0x35da0 (16 B) — forwards ecx, two zeros
extern int __stdcall MMAccessE(int, int, int);

int __fastcall MMAccessR(int a)
{
    return MMAccessE(a, 0, 0);
}
