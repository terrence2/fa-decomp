// _Rand8@0 @ rva 0x55900 (16 B) — mov ecx,0x100 / jmp @Rand32@4
extern long __fastcall Rand32(int);

long __stdcall Rand8(void)
{
    return Rand32(0x100);
}
