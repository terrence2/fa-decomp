// @MMAccessW@4 @ rva 0x35db0 (16 B)
extern int __stdcall MMAccessE(int, int, int);

int __fastcall MMAccessW(int a)
{
    return MMAccessE(a, 0, 0);
}
