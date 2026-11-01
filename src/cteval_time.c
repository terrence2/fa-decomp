// _CTEval_time @ rva 0x63fe0 (16 B) — FA loads the 16-B tick and masks;
//   our CL folds the mask away (xor first), so fitobj --patch restores
//   FA's exact "mov ax,moffs / and eax,0xffff / ret" (toolchain-diff).
extern unsigned short currentTime[];

long __cdecl CTEval_time(void)
{
    return *(unsigned short *)currentTime & 0xffff;
}
