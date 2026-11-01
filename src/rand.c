// @Rand@4 @ rva 0x55910 (16 B) — and ecx,0xffff / jmp @Rand32@4
extern long __fastcall Rand32(int);

long __fastcall Rand(int a)
{
    return Rand32(a & 0xffff);
}
