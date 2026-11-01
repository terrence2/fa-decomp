// @LimitEditFieldLength@4 @ rva 0x8b2b0 (16 B) — mov [dialPos320+0x40],ecx /
//   ret  (stores the fastcall arg to the C++-mangled WORD_POINT* global)
extern unsigned char dialPos320_x[];

void __fastcall LimitEditFieldLength(int a)
{
    *(long *)((char *)dialPos320_x + 0x40) = a;
}
