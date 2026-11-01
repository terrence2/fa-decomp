// @COLInit@0 @ rva 0x2e060 — xor eax,eax / mov [_specials+0x110],eax /
//   mov [_specials+0xe8],eax / ret. CL bakes the two offsets into the moffs
//   content itself (a3 form), so the map must NOT repeat the addends
//   (probe w5_colB exact).
extern long specials_x[];

void COLInit(void)
{
    long z = 0;
    specials_x[68] = z;
    specials_x[58] = z;
}
