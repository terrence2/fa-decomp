// _CTEval_do_nothing @ rva 0x63ff0 (16 B) — FA: cmp word[+50],1 /
//   sbb eax,eax / neg eax (borrow trick for t<1). Our CL 4.2 emits the
//   same semantics as mov eax,1 / adc eax,-1 (mov/adc form), so --patch
//   replaces the 8-byte tail with FA's 4-byte borrow form (toolchain-diff).
extern unsigned short serviceTicks[];

long __cdecl CTEval_do_nothing(void)
{
    return *(unsigned short *)(serviceTicks + 0x28) < 1;
}
