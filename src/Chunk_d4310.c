// w26a_d4310 @ rva 0xd4310 (870672, unnamed 8 B chunk) — FA bytes (raw):
//   8b 44 24 04          mov eax, [esp+4]
//   83 e0 7f             and eax, 0x7f
//   c3                   ret
// FPO params=1, fpo/esp frame: cdecl n -> n & 0x7f.
int w26a_d4310(int n)
{
    return n & 0x7f;
}