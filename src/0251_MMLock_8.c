// @MMLock@8 @ rva 0x35d40 (16 B) — forwards ecx, passes two zeros
extern int __stdcall MMAccessE(int, int, int);

int __fastcall MMLock(int a, int b)
{
    return MMAccessE(a, 0, 0);
}
