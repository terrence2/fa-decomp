// _Rand16@0 @ rva 0x558f0 (16 B) — mov ecx,0x10000 / jmp @Rand32@4
extern long __fastcall Rand32(int);

long __stdcall Rand16(void)
{
    return Rand32(0x10000);
}
