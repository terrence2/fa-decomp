// @WRInt@4 @ rva 0xb0a90 (8 B) — mov byte [_tint+4],cl / ret — store the
//   low byte of the fastcall arg at _tint+4.
extern unsigned char tint[];

void __fastcall WRInt(int a)
{
    *(unsigned char *)(tint + 4) = a;
}